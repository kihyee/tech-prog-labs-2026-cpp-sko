#pragma once
#include <algorithm>
#include <cmath>
#include "defense/damage_handler.hpp"

namespace lab3 {
    class ArmorHandler : public DamageHandler {
        double defense_;

    public:
        explicit ArmorHandler(double defense) : defense_(defense) {}
        void handle(Damage &damage) override {
            damage.reduceTo(std::max(1, static_cast<int>(std::lround(damage.getAmount() * (1 - defense_)))));
            passToNext(damage);
        }
    };
} // namespace lab3