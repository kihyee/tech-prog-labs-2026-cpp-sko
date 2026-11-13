#pragma once
#include "event/game_event.hpp"

namespace lab3 {
    class GameEventListener {
    public:
        virtual ~GameEventListener() = default;
        virtual void onEvent(const GameEvent &event) = 0;
    };
} // namespace lab3