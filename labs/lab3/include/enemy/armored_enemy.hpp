#pragma once
#include <stdexcept>
#include "enemy/enemy_decorator.hpp"

namespace lab3 {
    class ArmoredEnemy : public EnemyDecorator {
        std::string name_;

    public:
        explicit ArmoredEnemy(std::unique_ptr<Enemy> wrapped)
            : EnemyDecorator(std::move(wrapped)), name_("Бронированный " + wrapped_->getName()) {}
        const std::string &getName() const override {
            return name_;
        }
        Damage receiveHit(int amount) override {
            if (amount < 0)
                throw std::invalid_argument("Урон не может быть отрицательным");
            return amount == 0 ? Damage(0) : wrapped_->receiveHit(amount - amount / 2);
        }
    };
} // namespace lab3