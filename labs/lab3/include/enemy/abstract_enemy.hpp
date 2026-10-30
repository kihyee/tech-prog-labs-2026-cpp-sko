#pragma once

#include <string>

#include "combat/hit.hpp"
#include "enemy/enemy.hpp"

namespace lab3 {

    // общая логика для врагов: здоровье, урон в диапазоне, награда
    class AbstractEnemy : public Enemy {
    public:
        Hit rollDamage() override;

        int receiveHit(int damage) override;

        bool isAlive() const override;

        int rollGoldReward() const override;

        int getExperienceReward() const override;

        const std::string& getCode() const override;

        const std::string& getName() const override;

        int getHealth() const override;

        int getMaxHealth() const override;

    protected:
        AbstractEnemy(
            std::string code, std::string name, int maxHealth,
            int minDamage, int maxDamage,
            int experienceReward, int goldReward
        );

        // наследники могут уменьшать входящий урон
        virtual int reduceDamage(int damage) const;

    private:
        std::string code_;
        std::string name_;
        int maxHealth_;
        int minDamage_;
        int maxDamage_;
        int experienceReward_;
        int goldReward_;
        int health_;
    };

}  // namespace lab3