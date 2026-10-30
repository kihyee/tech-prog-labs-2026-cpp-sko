#pragma once

#include <string>

#include "combat/combatant.hpp"

namespace lab3 {

    // участник боя в том виде, в котором он попадает в отчет
    struct Participant {
        std::string code;
        std::string name;
        int maxHealth;

        static Participant of(const Combatant& combatant) {
            return {combatant.getCode(), combatant.getName(), combatant.getMaxHealth()};
        }
    };

}  // namespace lab3