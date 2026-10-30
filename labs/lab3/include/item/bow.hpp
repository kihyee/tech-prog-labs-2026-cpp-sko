#pragma once

#include <memory>
#include <string>

#include "item/weapon.hpp"

namespace lab3 {

    class Bow : public Weapon {
    public:
        Bow(std::string code, std::string name, int basePrice, int damage, double criticalChance);

        Hit rollDamage() const override;

        std::unique_ptr<Item> clone() const override;

        std::string getDescription() const override;

    private:
        static constexpr int CRITICAL_MULTIPLIER = 2;

        double criticalChance_;
    };

}  // namespace lab3