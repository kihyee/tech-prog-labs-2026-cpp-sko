#pragma once
#include <map>
#include "event/game_event_listener.hpp"

namespace lab3 {
    class ExpeditionJournal : public GameEventListener {
        std::map<std::string, std::vector<ExpeditionReport>> entries_;

    public:
        void onEvent(const GameEvent &e) override {
            entries_[e.hero.getName()].push_back(e.expedition);
        }
        std::vector<ExpeditionReport> getEntries(const std::string &name) const {
            auto it = entries_.find(name);
            return it == entries_.end() ? std::vector<ExpeditionReport>{} : it->second;
        }
    };
} // namespace lab3