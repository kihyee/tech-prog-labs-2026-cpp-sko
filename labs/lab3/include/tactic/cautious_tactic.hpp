#pragma once
#include "tactic/tactic.hpp"

namespace lab3 {
    class CautiousTactic : public Tactic {
    public:
        std::string getCode() const override {
            return "cautious";
        }
        std::string getDisplayName() const override {
            return "Осторожность";
        }
        std::string getDescription() const override {
            return "при здоровье ниже 40% через раунд уходить в оборону";
        }
        Action chooseAction(int round, const Combatant &hero, const Combatant &) const override {
            return hero.getHealth() < hero.getMaxHealth() * 0.4 && round % 2 == 0 ? Action::DEFEND
                                                                                  : Action::ATTACK;
        }
    };
} // namespace lab3