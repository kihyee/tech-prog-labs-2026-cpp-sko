#include <algorithm>
#include <cmath>
#include "combat/battle.hpp"

namespace lab3 {

    Battle::Battle(Combatant &hero, Combatant &enemy, const Tactic &tactic)
        : hero_(hero), enemy_(enemy), tactic_(tactic) {}

    BattleReport Battle::run() {
        while (hero_.isAlive() && enemy_.isAlive()) {
            round_++;
            Action action = tactic_.chooseAction(round_, hero_, enemy_);
            if (action == Action::POWER_STRIKE)
                emit({round_, EventType::POWER_STRIKE, Side::HERO, Side::ENEMY, 0, 0});
            else if (action == Action::DEFEND)
                emit({round_, EventType::DEFEND, Side::HERO, Side::HERO, 0, 0});
            strike(hero_, Side::HERO, enemy_, Side::ENEMY, attackMultiplier(action));
            if (enemy_.isAlive()) {
                strike(enemy_, Side::ENEMY, hero_, Side::HERO, incomingMultiplier(action));
            }
        }

        Outcome outcome = hero_.isAlive() ? Outcome::VICTORY : Outcome::DEFEAT;
        return {Participant::of(hero_), Participant::of(enemy_), outcome, events_};
    }

    void Battle::strike(Combatant &attacker, Side source, Combatant &defender, Side target, double multiplier) {
        Hit hit = attacker.rollDamage();
        Damage damage = defender.receiveHit(std::max(1, static_cast<int>(std::lround(hit.damage * multiplier))));
        if (damage.isEvaded()) {
            emit({round_, EventType::EVADE, source, target, 0, defender.getHealth()});
            return;
        }
        if (damage.getAbsorbed() > 0)
            emit({round_, EventType::ABSORB, source, target, damage.getAbsorbed(), defender.getHealth()});
        if (damage.getAmount() > 0)
            emit({round_, hit.critical ? EventType::CRITICAL_HIT : EventType::HIT, source, target,
                  damage.getAmount(), defender.getHealth()});

        if (!defender.isAlive()) {
            emit({round_, EventType::DEATH, source, target, 0, 0});
        }
    }

    void Battle::emit(const BattleEvent &event) {
        events_.push_back(event);
    }

} // namespace lab3