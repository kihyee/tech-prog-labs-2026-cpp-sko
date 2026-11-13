#pragma once

namespace lab3 {
    class Damage {
        int amount_;
        bool evaded_ = false;
        int absorbed_ = 0;

    public:
        explicit Damage(int amount) : amount_(amount) {}
        void reduceTo(int amount) {
            amount_ = amount;
        }
        void evade() {
            amount_ = 0;
            evaded_ = true;
        }
        void absorb(int value) {
            amount_ -= value;
            absorbed_ += value;
        }
        int getAmount() const {
            return amount_;
        }
        bool isEvaded() const {
            return evaded_;
        }
        int getAbsorbed() const {
            return absorbed_;
        }
    };
} // namespace lab3