#pragma once
#include <algorithm>
#include <memory>
#include <utility>
#include "core/dice.hpp"
#include "enemy/enemy.hpp"
#include "item/weapon.hpp"

namespace lab3 {
    class HauntedWeapon : public Enemy {
        std::shared_ptr<Weapon> weapon_;
        std::string code_ = "haunted-weapon", name_;
        int maxHealth_, health_;

    public:
        explicit HauntedWeapon(std::shared_ptr<Weapon> weapon)
            : weapon_(std::move(weapon)), name_("Одержимый " + weapon_->getName()),
              maxHealth_(weapon_->getDamage() * 5), health_(maxHealth_) {}
        const std::string &getCode() const override {
            return code_;
        }
        const std::string &getName() const override {
            return name_;
        }
        int getHealth() const override {
            return health_;
        }
        int getMaxHealth() const override {
            return maxHealth_;
        }
        bool isAlive() const override {
            return health_ > 0;
        }
        Hit rollDamage() override {
            return weapon_->rollDamage();
        }
        Damage receiveHit(int amount) override {
            health_ = std::max(0, health_ - amount);
            return Damage(amount);
        }
        int getExperienceReward() const override {
            return weapon_->getPrice() / 2;
        }
        int rollGoldReward() const override {
            return Dice::getInstance().roll(weapon_->getPrice() / 4, weapon_->getPrice() / 2);
        }
    };
} // namespace lab3