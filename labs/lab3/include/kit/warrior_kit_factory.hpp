#pragma once

#include <memory>

#include "item/default_catalog.hpp"
#include "item/item_catalog.hpp"
#include "kit/starter_kit_factory.hpp"

namespace lab3 {

    class WarriorKitFactory : public StarterKitFactory {
    public:
        explicit WarriorKitFactory(const ItemCatalog& catalog) : catalog_(catalog) {}

        std::unique_ptr<Weapon> createWeapon() const override {
            return catalog_.createWeapon(item_codes::TRAINING_SWORD);
        }

        std::unique_ptr<Armor> createArmor() const override {
            return catalog_.createArmor(item_codes::CHAINMAIL);
        }

    private:
        const ItemCatalog& catalog_;
    };

}  // namespace lab3