#pragma once
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include "event/game_event_listener.hpp"

namespace lab3 {
    class GameEventPublisher {
        std::map<GameEventType, std::vector<std::shared_ptr<GameEventListener>>> listeners_;

    public:
        void subscribe(GameEventType type, std::shared_ptr<GameEventListener> listener) {
            listeners_[type].push_back(std::move(listener));
        }
        void unsubscribe(GameEventType type, const std::shared_ptr<GameEventListener> &listener) {
            std::erase(listeners_[type], listener);
        }
        void publish(const GameEvent &event) {
            auto listeners = listeners_[event.type];
            for (auto &listener : listeners)
                listener->onEvent(event);
        }
    };
} // namespace lab3