#include "combat/battle.hpp"

namespace lab3 {

    Battle::Battle(Combatant& hero, Combatant& enemy) : hero_(hero), enemy_(enemy) {}

    BattleReport Battle::run() {
        while (hero_.isAlive() && enemy_.isAlive()) {
            round_++;
            strike(hero_, Side::HERO, enemy_, Side::ENEMY);
            if (enemy_.isAlive()) {
                strike(enemy_, Side::ENEMY, hero_, Side::HERO);
            }
        }

        Outcome outcome = hero_.isAlive() ? Outcome::VICTORY : Outcome::DEFEAT;
        return {Participant::of(hero_), Participant::of(enemy_), outcome, events_};
    }

    void Battle::strike(Combatant& attacker, Side source, Combatant& defender, Side target) {
        Hit hit = attacker.rollDamage();
        int dealt = defender.receiveHit(hit.damage);
        EventType type = hit.critical ? EventType::CRITICAL_HIT : EventType::HIT;
        emit({round_, type, source, target, dealt, defender.getHealth()});

        if (!defender.isAlive()) {
            emit({round_, EventType::DEATH, source, target, 0, 0});
        }
    }

    void Battle::emit(const BattleEvent& event) {
        events_.push_back(event);
    }

}  // namespace lab3