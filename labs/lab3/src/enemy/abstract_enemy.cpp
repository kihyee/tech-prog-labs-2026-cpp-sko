#include "enemy/abstract_enemy.hpp"

#include <algorithm>
#include <utility>

#include "core/dice.hpp"

namespace lab3 {

    AbstractEnemy::AbstractEnemy(
        std::string code, std::string name, int maxHealth,
        int minDamage, int maxDamage,
        int experienceReward, int goldReward
    )
        : code_(std::move(code)),
          name_(std::move(name)),
          maxHealth_(maxHealth),
          minDamage_(minDamage),
          maxDamage_(maxDamage),
          experienceReward_(experienceReward),
          goldReward_(goldReward),
          health_(maxHealth) {}

    Hit AbstractEnemy::rollDamage() {
        return {Dice::getInstance().roll(minDamage_, maxDamage_), false};
    }

    int AbstractEnemy::receiveHit(int damage) {
        int dealt = std::max(1, reduceDamage(damage));
        health_ = std::max(0, health_ - dealt);
        return dealt;
    }

    int AbstractEnemy::reduceDamage(int damage) const {
        return damage;
    }

    bool AbstractEnemy::isAlive() const {
        return health_ > 0;
    }

    int AbstractEnemy::rollGoldReward() const {
        return Dice::getInstance().roll(goldReward_ / 2, goldReward_);
    }

    int AbstractEnemy::getExperienceReward() const {
        return experienceReward_;
    }

    const std::string& AbstractEnemy::getCode() const {
        return code_;
    }

    const std::string& AbstractEnemy::getName() const {
        return name_;
    }

    int AbstractEnemy::getHealth() const {
        return health_;
    }

    int AbstractEnemy::getMaxHealth() const {
        return maxHealth_;
    }

}  // namespace lab3