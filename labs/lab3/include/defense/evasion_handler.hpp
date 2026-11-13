#pragma once
#include "core/dice.hpp"
#include "defense/damage_handler.hpp"

namespace lab3 {
    class EvasionHandler : public DamageHandler {
        double chance_;

    public:
        explicit EvasionHandler(double chance) : chance_(chance) {}
        void handle(Damage &damage) override {
            if (Dice::getInstance().chance(chance_)) {
                damage.evade();
                return;
            }
            passToNext(damage);
        }
    };
} // namespace lab3