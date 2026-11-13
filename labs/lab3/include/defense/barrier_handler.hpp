#pragma once
#include <algorithm>
#include "defense/damage_handler.hpp"

namespace lab3 {
    class BarrierHandler : public DamageHandler {
        int strength_;

    public:
        explicit BarrierHandler(int strength) : strength_(strength) {}
        void handle(Damage &damage) override {
            int absorbed = std::min(strength_, damage.getAmount());
            if (absorbed > 0) {
                strength_ -= absorbed;
                damage.absorb(absorbed);
            }
            passToNext(damage);
        }
    };
} // namespace lab3