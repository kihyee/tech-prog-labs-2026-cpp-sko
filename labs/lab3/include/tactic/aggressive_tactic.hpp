#pragma once
#include "tactic/tactic.hpp"

namespace lab3 {
    class AggressiveTactic : public Tactic {
    public:
        std::string getCode() const override {
            return "aggressive";
        }
        std::string getDisplayName() const override {
            return "Натиск";
        }
        std::string getDescription() const override {
            return "совершать безрассудные удары, пока у врага больше здоровья, чем у героя";
        }
        Action chooseAction(int, const Combatant &hero, const Combatant &enemy) const override {
            return enemy.getHealth() > hero.getHealth() ? Action::POWER_STRIKE : Action::ATTACK;
        }
    };
} // namespace lab3