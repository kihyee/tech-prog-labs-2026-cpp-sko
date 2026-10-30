#pragma once

#include <memory>
#include <string>
#include <vector>

#include "enemy/skeleton.hpp"
#include "item/default_catalog.hpp"
#include "world/location.hpp"

namespace lab3 {

    class Crypt : public Location {
    public:
        inline static const std::string CODE = "crypt";

        explicit Crypt(const ItemCatalog& catalog) : Location(CODE, "Заброшенный склеп", 3, catalog) {}

    protected:
        std::unique_ptr<Enemy> createEnemy() const override {
            return std::make_unique<Skeleton>();
        }

        const std::vector<std::string>& getLootTable() const override {
            static const std::vector<std::string> loot{
                item_codes::KNIGHT_BLADE, item_codes::BONE_BOW, item_codes::NECROMANCER_STAFF, item_codes::CRYPT_MAIL};
            return loot;
        }
    };

}  // namespace lab3