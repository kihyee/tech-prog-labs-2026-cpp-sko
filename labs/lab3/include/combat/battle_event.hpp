#pragma once

#include "combat/event_type.hpp"
#include "combat/side.hpp"

namespace lab3 {

    struct BattleEvent {
        int round;
        EventType type;
        Side source;
        Side target;
        int amount;
        int targetHealthAfter;
    };

}  // namespace lab3