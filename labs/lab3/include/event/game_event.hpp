#pragma once
#include "event/game_event_type.hpp"
#include "hero/hero.hpp"
#include "world/expedition_report.hpp"

namespace lab3 {
    struct GameEvent {
        GameEventType type;
        Hero &hero;
        ExpeditionReport expedition;
    };
} // namespace lab3