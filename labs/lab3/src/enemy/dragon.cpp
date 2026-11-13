#include "defense/armor_handler.hpp"
#include "enemy/dragon.hpp"

#include <cmath>

#include "core/dice.hpp"

namespace lab3 {

    Dragon::Dragon()
        : AbstractEnemy("dragon", "Дракон", 260, 16, 22, 500, 400, std::make_unique<ArmorHandler>(RESISTANCE)) {}

    Hit Dragon::rollDamage() {
        Hit bite = AbstractEnemy::rollDamage();
        if (Dice::getInstance().chance(FIRE_BREATH_CHANCE)) {
            return {bite.damage * FIRE_BREATH_MULTIPLIER, true};
        }

        return bite;
    }

} // namespace lab3