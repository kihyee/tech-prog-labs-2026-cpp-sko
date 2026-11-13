#pragma once
#include "tactic/tactic.hpp"

namespace lab3 {
    class BalancedTactic : public Tactic {
    public:
        std::string getCode() const override {
            return "balanced";
        }
        std::string getDisplayName() const override {
            return "Баланс";
        }
        std::string getDescription() const override {
            return "обычный удар каждый раунд";
        }
        Action chooseAction(int, const Combatant &, const Combatant &) const override {
            return Action::ATTACK;
        }
    };
} // namespace lab3