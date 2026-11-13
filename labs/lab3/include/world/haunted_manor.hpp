#pragma once
#include "world/location.hpp"
#include "enemy/haunted_weapon.hpp"
#include "item/default_catalog.hpp"

namespace lab3 {
    class HauntedManor : public Location {
        const std::vector<std::string> weapons_{item_codes::IRON_SWORD, item_codes::ELVEN_BOW,
                                                item_codes::EMBER_STAFF};

    public:
        explicit HauntedManor(const ItemCatalog &catalog)
            : Location("haunted-manor", "Проклятый особняк", 2, catalog) {}

    protected:
        std::unique_ptr<Enemy> createEnemy() const override {
            return std::make_unique<HauntedWeapon>(getCatalog().createWeapon(Dice::getInstance().pick(weapons_)));
        }
        const std::vector<std::string> &getLootTable() const override {
            return weapons_;
        }
    };
} // namespace lab3