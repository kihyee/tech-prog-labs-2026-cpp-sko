#pragma once

#include "combat/combatant.hpp"

namespace lab3 {

    class Enemy : public Combatant {
    public:
        virtual int getExperienceReward() const = 0;

        virtual int rollGoldReward() const = 0;
    };

}  // namespace lab3