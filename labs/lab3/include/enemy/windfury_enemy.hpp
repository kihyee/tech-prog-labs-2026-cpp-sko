#pragma once
#include <stdexcept>
#include "enemy/enemy_decorator.hpp"

namespace lab3 {
    class WindfuryEnemy : public EnemyDecorator {
        std::string name_;

    public:
        explicit WindfuryEnemy(std::unique_ptr<Enemy> wrapped)
            : EnemyDecorator(std::move(wrapped)), name_("Неистовый " + wrapped_->getName()) {}
        const std::string &getName() const override {
            return name_;
        }
        Hit rollDamage() override {
            auto first = wrapped_->rollDamage();
            auto second = wrapped_->rollDamage();
            return {first.damage + second.damage, first.critical || second.critical};
        }
        int getExperienceReward() const override {
            int r = wrapped_->getExperienceReward();
            return r + r * 50 / 100;
        }
        int rollGoldReward() const override {
            int r = wrapped_->rollGoldReward();
            return r + r * 50 / 100;
        }
    };
} // namespace lab3