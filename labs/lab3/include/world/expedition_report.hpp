#pragma once

#include <cstdint>
#include <string>

#include "combat/battle_report.hpp"
#include "world/rewards.hpp"

namespace lab3 {

    // отчет об экспедиции: с каким сидом, куда, как прошел бой и что получил герой
    struct ExpeditionReport {
        std::uint32_t seed;
        std::string locationCode;
        BattleReport battle;
        Rewards rewards;
    };

}  // namespace lab3