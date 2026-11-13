#pragma once
#include <memory>
#include <utility>
#include "enemy/enemy.hpp"

namespace lab3 {
    class EnemyDecorator : public Enemy {
    protected:
        std::unique_ptr<Enemy> wrapped_;

    public:
        explicit EnemyDecorator(std::unique_ptr<Enemy> wrapped) : wrapped_(std::move(wrapped)) {}
        const std::string &getCode() const override {
            return wrapped_->getCode();
        }
        const std::string &getName() const override {
            return wrapped_->getName();
        }
        int getHealth() const override {
            return wrapped_->getHealth();
        }
        int getMaxHealth() const override {
            return wrapped_->getMaxHealth();
        }
        bool isAlive() const override {
            return wrapped_->isAlive();
        }
        Hit rollDamage() override {
            return wrapped_->rollDamage();
        }
        Damage receiveHit(int amount) override {
            return wrapped_->receiveHit(amount);
        }
        int getExperienceReward() const override {
            return wrapped_->getExperienceReward();
        }
        int rollGoldReward() const override {
            return wrapped_->rollGoldReward();
        }
    };
} // namespace lab3