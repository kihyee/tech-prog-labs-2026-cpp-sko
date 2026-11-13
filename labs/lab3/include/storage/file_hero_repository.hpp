#pragma once
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include "nlohmann/json.hpp"
#include "storage/hero_repository.hpp"
#include "item/item_catalog.hpp"

namespace lab3 {
class FileHeroRepository : public HeroRepository {
    using Json = nlohmann::ordered_json;
    std::filesystem::path file_;
    const ItemCatalog &catalog_;
    std::string pathText() const {
        auto text = file_.u8string();
        return std::string(text.begin(), text.end());
    }
    static Json snapshotItem(const Item &item) {
        Json codes = Json::array();
        for (auto e : item.getEnchantments())
            codes.push_back(e->code);
        return {{"code", item.getCode()}, {"enchantments", codes}};
    }
    static Json snapshot(const Hero &hero) {
        Json inventory = Json::array(), achievements = Json::array();
        for (auto &item : hero.getInventory())
            inventory.push_back(snapshotItem(*item));
        for (auto a : hero.getAchievements())
            achievements.push_back(a->code);
        return {{"name", hero.getName()},
                {"heroClass", hero.getHeroClass().getCode()},
                {"level", hero.getLevel()},
                {"experience", hero.getExperience()},
                {"gold", hero.getGold()},
                {"weapon", snapshotItem(hero.getWeapon())},
                {"armor", snapshotItem(hero.getArmor())},
                {"inventory", inventory},
                {"achievements", achievements}};
    }
    std::shared_ptr<Item> restoreItem(const Json &save) const {
        std::shared_ptr<Item> item = catalog_.create(save.at("code").get<std::string>());
        for (auto &code : save.at("enchantments"))
            item->enchant(enchantments::byCode(code.get<std::string>()));
        return item;
    }
    std::shared_ptr<Hero> restore(const Json &save) const {
        std::vector<std::shared_ptr<Item>> inventory;
        for (auto &item : save.at("inventory"))
            inventory.push_back(restoreItem(item));
        std::vector<const Achievement *> achievements;
        for (auto &code : save.at("achievements"))
            achievements.push_back(&achievements::byCode(code.get<std::string>()));
        return std::make_shared<Hero>(
            Hero::Builder()
                .setName(save.at("name").get<std::string>())
                .setHeroClass(HeroClass::byCode(save.at("heroClass").get<std::string>()))
                .setLevel(save.at("level").get<int>())
                .setExperience(save.at("experience").get<int>())
                .setGold(save.at("gold").get<int>())
                .setWeapon(std::dynamic_pointer_cast<Weapon>(restoreItem(save.at("weapon"))))
                .setArmor(std::dynamic_pointer_cast<Armor>(restoreItem(save.at("armor"))))
                .setInventory(std::move(inventory))
                .setAchievements(std::move(achievements))
                .build());
    }

  public:
    FileHeroRepository(std::filesystem::path file, const ItemCatalog &catalog)
        : file_(std::move(file)), catalog_(catalog) {}
    std::vector<std::shared_ptr<Hero>> findAll() override {
        if (!std::filesystem::exists(file_))
            return {};
        std::ifstream input(file_, std::ios::binary);
        if (!input)
            throw std::runtime_error("Не удалось открыть сохранение: " + pathText());
        std::string text((std::istreambuf_iterator<char>(input)), {});
        if (input.bad())
            throw std::runtime_error("Ошибка чтения сохранения: " + pathText());
        if (text.find_first_not_of(" \t\r\n") == std::string::npos)
            return {};
        auto saves = Json::parse(text);
        if (!saves.is_array())
            throw std::runtime_error("В файле должен быть массив героев");
        std::vector<std::shared_ptr<Hero>> result;
        for (auto &save : saves)
            result.push_back(restore(save));
        return result;
    }
    std::shared_ptr<Hero> findByName(const std::string &name) override {
        for (auto &h : findAll())
            if (h->getName() == name)
                return h;
        return nullptr;
    }
    void save(const std::shared_ptr<Hero> &hero) override {
        Json saves = Json::array();
        for (auto &h : findAll())
            if (h->getName() != hero->getName())
                saves.push_back(snapshot(*h));
        saves.push_back(snapshot(*hero));
        auto parent = std::filesystem::absolute(file_).parent_path();
        std::filesystem::create_directories(parent);
        std::ofstream output(file_, std::ios::binary | std::ios::trunc);
        output << saves.dump(2) << '\n';
        output.close();
        if (!output)
            throw std::runtime_error("Не удалось записать сохранение: " + pathText());
    }
};
} // namespace lab3