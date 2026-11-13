#pragma once
#include "tactic/tactic.hpp"

#include <vector>

#include "combat/battle_event.hpp"
#include "combat/battle_report.hpp"
#include "combat/combatant.hpp"
#include "combat/side.hpp"

namespace lab3 {

    // бой идет по раундам: сначала бьет герой, потом враг, пока кто-то не погибнет
    class Battle {
    public:
        Battle(Combatant &hero, Combatant &enemy, const Tactic &tactic);

        BattleReport run();

    private:
        void strike(Combatant &attacker, Side source, Combatant &defender, Side target, double multiplier);

        void emit(const BattleEvent &event);

        Combatant &hero_;
        Combatant &enemy_;
        std::vector<BattleEvent> events_;
        int round_ = 0;
        const Tactic &tactic_;
    };

} // namespace lab3