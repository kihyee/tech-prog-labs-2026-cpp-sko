#pragma once
#include <string>
#include "combat/combatant.hpp"
#include "tactic/action.hpp"

namespace lab3 {
    class Tactic {
    public:
        virtual ~Tactic() = default;
        virtual std::string getCode() const = 0;
        virtual std::string getDisplayName() const = 0;
        virtual std::string getDescription() const = 0;
        virtual Action chooseAction(int round, const Combatant &hero, const Combatant &enemy) const = 0;
    };
} // namespace lab3