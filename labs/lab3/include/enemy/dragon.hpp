#pragma once

#include "enemy/abstract_enemy.hpp"

namespace lab3 {

    // дракон защищен чешуей и время от времени дышит огнем
    class Dragon : public AbstractEnemy {
    public:
        Dragon();

        Hit rollDamage() override;

    protected:
        int reduceDamage(int damage) const override;

    private:
        static constexpr double RESISTANCE = 0.25;
        static constexpr double FIRE_BREATH_CHANCE = 0.25;
        static constexpr int FIRE_BREATH_MULTIPLIER = 2;
    };

}  // namespace lab3