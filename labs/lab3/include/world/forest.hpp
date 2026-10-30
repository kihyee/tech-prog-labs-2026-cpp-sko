#pragma once

#include <memory>
#include <string>
#include <vector>

#include "enemy/goblin.hpp"
#include "item/default_catalog.hpp"
#include "world/location.hpp"

namespace lab3 {

    class Forest : public Location {
    public:
        inline static const std::string CODE = "forest";

        explicit Forest(const ItemCatalog& catalog) : Location(CODE, "Мистический лес", 1, catalog) {}

    protected:
        std::unique_ptr<Enemy> createEnemy() const override {
            return std::make_unique<Goblin>();
        }

        const std::vector<std::string>& getLootTable() const override {
            static const std::vector<std::string> loot{
                item_codes::GOBLIN_CLEAVER, item_codes::HUNTING_BOW, item_codes::LEATHER_ARMOR};
            return loot;
        }
    };

}  // namespace lab3