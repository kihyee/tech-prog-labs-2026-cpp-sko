#include "enemy/abstract_enemy.hpp"

#include <algorithm>
#include <utility>

#include "core/dice.hpp"

namespace lab3 {

    AbstractEnemy::AbstractEnemy(std::string code, std::string name, int maxHealth, int minDamage, int maxDamage,
                                 int experienceReward, int goldReward, std::unique_ptr<DamageHandler> defense)
        : code_(std::move(code)), name_(std::move(name)), maxHealth_(maxHealth), minDamage_(minDamage),
          maxDamage_(maxDamage), experienceReward_(experienceReward), goldReward_(goldReward), health_(maxHealth),
          defense_(std::move(defense)) {}

    Hit AbstractEnemy::rollDamage() {
        return {Dice::getInstance().roll(minDamage_, maxDamage_), false};
    }

    Damage AbstractEnemy::receiveHit(int amount) {
        Damage damage(amount);
        if (defense_)
            defense_->handle(damage);
        health_ = std::max(0, health_ - damage.getAmount());
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

    const std::string &AbstractEnemy::getCode() const {
        return code_;
    }

    const std::string &AbstractEnemy::getName() const {
        return name_;
    }

    int AbstractEnemy::getHealth() const {
        return health_;
    }

    int AbstractEnemy::getMaxHealth() const {
        return maxHealth_;
    }

} // namespace lab3