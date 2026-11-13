#pragma once

namespace lab3 {
    enum class Action { ATTACK, POWER_STRIKE, DEFEND };
    inline double attackMultiplier(Action action) {
        return action == Action::POWER_STRIKE ? 1.5 : action == Action::DEFEND ? 0.5 : 1.0;
    }
    inline double incomingMultiplier(Action action) {
        return action == Action::POWER_STRIKE ? 1.5 : action == Action::DEFEND ? 0.3 : 1.0;
    }
} // namespace lab3