#include "item/item_catalog.hpp"

#include <stdexcept>
#include <utility>

#include "core/unknown_code_error.hpp"

namespace lab3 {

    void ItemCatalog::add(std::unique_ptr<Item> prototype) {
        prototypes_.push_back(std::move(prototype));
    }

    std::unique_ptr<Item> ItemCatalog::create(const std::string& code) const {
        for (const auto& prototype : prototypes_) {
            if (prototype->getCode() == code) {
                return prototype->clone();
            }
        }

        throw UnknownCodeError("Предмет", code);
    }

    std::unique_ptr<Weapon> ItemCatalog::createWeapon(const std::string& code) const {
        std::unique_ptr<Item> item = create(code);
        if (auto* weapon = dynamic_cast<Weapon*>(item.get())) {
            // передаем владение копией из unique_ptr<Item> в unique_ptr<Weapon>
            item.release();
            return std::unique_ptr<Weapon>(weapon);
        }

        throw std::invalid_argument("Предмет '" + code + "' не является оружием");
    }

    std::unique_ptr<Armor> ItemCatalog::createArmor(const std::string& code) const {
        std::unique_ptr<Item> item = create(code);
        if (auto* armor = dynamic_cast<Armor*>(item.get())) {
            item.release();
            return std::unique_ptr<Armor>(armor);
        }

        throw std::invalid_argument("Предмет '" + code + "' не является броней");
    }

    std::vector<std::string> ItemCatalog::getCodes() const {
        std::vector<std::string> codes;
        for (const auto& prototype : prototypes_) {
            codes.push_back(prototype->getCode());
        }

        return codes;
    }

}  // namespace lab3