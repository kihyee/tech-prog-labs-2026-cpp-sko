#pragma once

#include <memory>

#include "item/item.hpp"

namespace lab3 {

    // итоги экспедиции для героя;
    // gold отрицательный, если герой проиграл и потерял золото, loot пустой, если добычи нет
    struct Rewards {
        int experience;
        int gold;
        std::shared_ptr<Item> loot;
        int levelsGained;
    };

}  // namespace lab3