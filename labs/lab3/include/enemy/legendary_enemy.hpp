#pragma once
#include <stdexcept>
#include "enemy/enemy_decorator.hpp"

namespace lab3 {
    class LegendaryEnemy : public EnemyDecorator {
        std::string name_;

    public:
        explicit LegendaryEnemy(std::unique_ptr<Enemy> wrapped)
            : EnemyDecorator(std::move(wrapped)), name_("Легендарный " + wrapped_->getName()) {}
        const std::string &getName() const override {
            return name_;
        }
        Hit rollDamage() override {
            auto hit = wrapped_->rollDamage();
            hit.damage *= 2;
            return hit;
        }
        int getExperienceReward() const override {
            return wrapped_->getExperienceReward() * 2;
        }
        int rollGoldReward() const override {
            return wrapped_->rollGoldReward() * 2;
        }
    };
} // namespace lab3