#pragma once

#include "enemy/abstract_enemy.hpp"

namespace lab3 {

    // гоблин - самый простой враг, без особенностей
    class Goblin : public AbstractEnemy {
    public:
        Goblin() : AbstractEnemy("goblin", "Гоблин", 50, 6, 14, 40, 30) {}
    };

}  // namespace lab3