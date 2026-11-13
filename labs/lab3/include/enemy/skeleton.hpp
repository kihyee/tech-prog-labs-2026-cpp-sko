#pragma once
#include "defense/armor_handler.hpp"

#include <cmath>

#include "enemy/abstract_enemy.hpp"

namespace lab3 {

    // скелет: кости плохо поддаются ударам, поэтому часть урона проходит мимо
    class Skeleton : public AbstractEnemy {
    public:
        Skeleton()
            : AbstractEnemy("skeleton", "Скелет", 110, 10, 24, 90, 70,
                            std::make_unique<ArmorHandler>(RESISTANCE)) {}

    private:
        static constexpr double RESISTANCE = 0.3;
    };

} // namespace lab3