#pragma once

#include <vector>

#include "combat/battle_event.hpp"
#include "combat/outcome.hpp"
#include "combat/participant.hpp"

namespace lab3 {

    // результат боя: кто сражался, чем все закончилось и что происходило по ходу дела
    struct BattleReport {
        Participant hero;
        Participant enemy;
        Outcome outcome;
        std::vector<BattleEvent> events;
    };

}  // namespace lab3