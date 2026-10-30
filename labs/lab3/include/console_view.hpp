#pragma once

#include <string>

#include "combat/battle_event.hpp"
#include "combat/battle_report.hpp"
#include "combat/participant.hpp"
#include "combat/side.hpp"
#include "hero/hero.hpp"
#include "item/item.hpp"
#include "world/expedition_report.hpp"
#include "world/rewards.hpp"

namespace lab3 {

    // весь вывод в консоль собран здесь
    class ConsoleView {
    public:
        static void setupConsole();

        std::string describe(const Item& item) const;

        void printHero(const Hero& hero) const;

        void printReport(const ExpeditionReport& report, const std::string& locationName) const;

    private:
        void printEvent(const BattleEvent& event, const BattleReport& battle) const;

        void printRewards(const BattleReport& battle, const Rewards& rewards) const;

        const Participant& participant(Side side, const BattleReport& battle) const;
    };

}  // namespace lab3