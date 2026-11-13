#pragma once
#include "defense/damage_handler.hpp"

#include <string>

#include "combat/hit.hpp"
#include "enemy/enemy.hpp"

namespace lab3 {

    // общая логика для врагов: здоровье, урон в диапазоне, награда
    class AbstractEnemy : public Enemy {
    public:
        Hit rollDamage() override;

        Damage receiveHit(int damage) override;

        bool isAlive() const override;

        int rollGoldReward() const override;

        int getExperienceReward() const override;

        const std::string &getCode() const override;

        const std::string &getName() const override;

        int getHealth() const override;

        int getMaxHealth() const override;

    protected:
        AbstractEnemy(std::string code, std::string name, int maxHealth, int minDamage, int maxDamage,
                      int experienceReward, int goldReward, std::unique_ptr<DamageHandler> defense = nullptr);

    private:
        std::string code_;
        std::string name_;
        int maxHealth_;
        int minDamage_;
        int maxDamage_;
        int experienceReward_;
        int goldReward_;
        int health_;
        std::unique_ptr<DamageHandler> defense_;
    };

} // namespace lab3