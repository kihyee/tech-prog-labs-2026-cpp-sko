#pragma once
#include <memory>
#include <utility>
#include "defense/damage.hpp"

namespace lab3 {
    class DamageHandler {
        std::unique_ptr<DamageHandler> next_;

    public:
        virtual ~DamageHandler() = default;
        DamageHandler &setNext(std::unique_ptr<DamageHandler> next) {
            next_ = std::move(next);
            return *next_;
        }
        virtual void handle(Damage &damage) = 0;

    protected:
        void passToNext(Damage &damage) {
            if (next_)
                next_->handle(damage);
        }
    };
} // namespace lab3