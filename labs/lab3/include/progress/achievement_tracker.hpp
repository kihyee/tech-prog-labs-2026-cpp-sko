#pragma once
#include "event/game_event_listener.hpp"
#include "progress/achievement.hpp"

namespace lab3 {
    class AchievementTracker : public GameEventListener {
    public:
        void onEvent(const GameEvent &e) override {
            if (e.type == GameEventType::VICTORY) {
                e.hero.unlock(achievements::FIRST_BLOOD);
                if (e.expedition.battle.enemy.code == "dragon")
                    e.hero.unlock(achievements::DRAGON_SLAYER);
                auto loot = e.expedition.rewards.loot;
                if (loot && !loot->getEnchantments().empty())
                    e.hero.unlock(achievements::LUCKY);
            } else if (e.type == GameEventType::LEVEL_UP && e.hero.getLevel() >= 5)
                e.hero.unlock(achievements::VETERAN);
        }
    };
} // namespace lab3