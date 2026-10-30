#pragma once

#include <memory>
#include <string>
#include <vector>

#include "combat/combatant.hpp"
#include "combat/hit.hpp"
#include "hero/hero_class.hpp"
#include "item/armor.hpp"
#include "item/item.hpp"
#include "item/weapon.hpp"
#include "kit/starter_kit_factory.hpp"

namespace lab3 {

class Hero : public Combatant {
public:
    // внутренний класс билдер - чтобы удобно и безопасно создавать героев
    class Builder {
    public:
        Builder& setName(std::string name);

        Builder& setHeroClass(const HeroClass& heroClass);

        Builder& setWeapon(std::shared_ptr<Weapon> weapon);

        Builder& setArmor(std::shared_ptr<Armor> armor);

        // берет оружие и броню из стартового набора
        Builder& setStarterKit(const StarterKitFactory& starterKit);

        Builder& setLevel(int level);

        Builder& setGold(int gold);

        // перед созданием героя проверяем, что все обязательные поля заполнены корректно
        Hero build() const;

    private:
        // герою нужен доступ к полям строителя
        friend class Hero;

        std::string name_;
        const HeroClass* heroClass_ = nullptr;
        std::shared_ptr<Weapon> weapon_;
        std::shared_ptr<Armor> armor_;
        // необязательные поля сразу получают значения по умолчанию
        int level_ = 1;
        int gold_ = STARTING_GOLD;
    };

    // героя можно перемещать, но не копировать: копия делила бы с оригиналом все его предметы
    Hero(const Hero&) = delete;
    Hero& operator=(const Hero&) = delete;
    Hero(Hero&&) = default;
    Hero& operator=(Hero&&) = default;

    Hit rollDamage() override;

    int receiveHit(int damage) override;

    bool isAlive() const override;

    // поведение героя между экспедициями

    // перед каждой экспедицией герой успевает отдохнуть
    void restoreHealth();

    // начисляет опыт, возвращает количество полученных уровней
    int gainExperience(int amount);

    void addGold(int amount);

    void spendGold(int amount);

    void addItem(std::shared_ptr<Item> item);

    void removeItem(const std::shared_ptr<Item>& item);

    // экипирует предмет из инвентаря, снятый предмет возвращается в инвентарь
    void equip(const std::shared_ptr<Item>& item);

    // геттеры

    const std::string& getCode() const override;

    const std::string& getName() const override;

    int getHealth() const override;

    int getMaxHealth() const override;

    const HeroClass& getHeroClass() const;

    int getLevel() const;

    int getExperience() const;

    int getExperienceToNextLevel() const;

    int getGold() const;

    const Weapon& getWeapon() const;

    const Armor& getArmor() const;

    const std::vector<std::shared_ptr<Item>>& getInventory() const;

private:
    static constexpr int MAX_NAME_LENGTH = 20;
    static constexpr int STARTING_GOLD = 50;
    static constexpr int HEALTH_PER_LEVEL = 15;
    static constexpr int DAMAGE_PER_LEVEL = 3;
    static constexpr int EXPERIENCE_PER_LEVEL = 100;

    // конструктор приватный и принимает в себя билдера, из которого и берет значения полей
    explicit Hero(const Builder& builder);

    std::string name_;
    const HeroClass* heroClass_;
    int level_;
    int experience_ = 0;
    int gold_;
    int health_;
    // предметы хранятся в shared_ptr: на один и тот же предмет могут ссылаться,
    // например, инвентарь героя и отчет об экспедиции, в котором он выпал
    std::shared_ptr<Weapon> weapon_;
    std::shared_ptr<Armor> armor_;
    std::vector<std::shared_ptr<Item>> inventory_;
};

}  // namespace lab3