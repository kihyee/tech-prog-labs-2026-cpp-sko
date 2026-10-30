#pragma once

#include <memory>
#include <string>
#include <vector>

#include "enemy/dragon.hpp"
#include "item/default_catalog.hpp"
#include "world/location.hpp"

namespace lab3 {

    class DragonLair : public Location {
    public:
        inline static const std::string CODE = "dragon-lair";

        explicit DragonLair(const ItemCatalog& catalog) : Location(CODE, "Логово дракона", 5, catalog) {}

    protected:
        std::unique_ptr<Enemy> createEnemy() const override {
            return std::make_unique<Dragon>();
        }

        const std::vector<std::string>& getLootTable() const override {
            static const std::vector<std::string> loot{item_codes::DAWN_BLADE, item_codes::DRAGONSCALE_ARMOR};
            return loot;
        }
    };

}  // namespace lab3