#pragma once

#include <cmath>

#include "enemy/abstract_enemy.hpp"

namespace lab3 {

    // скелет: кости плохо поддаются ударам, поэтому часть урона проходит мимо
    class Skeleton : public AbstractEnemy {
    public:
        Skeleton() : AbstractEnemy("skeleton", "Скелет", 110, 10, 24, 90, 70) {}

    protected:
        int reduceDamage(int damage) const override {
            return static_cast<int>(std::lround(damage * (1 - RESISTANCE)));
        }

    private:
        static constexpr double RESISTANCE = 0.3;
    };

}  // namespace lab3