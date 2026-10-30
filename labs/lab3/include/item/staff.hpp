#pragma once

#include <memory>
#include <string>

#include "item/weapon.hpp"

namespace lab3 {

    // урон посоха непредсказуем: он может быть как больше, так и меньше базового
    class Staff : public Weapon {
    public:
        Staff(std::string code, std::string name, int basePrice, int damage, double scatter);

        Hit rollDamage() const override;

        std::unique_ptr<Item> clone() const override;

        std::string getDescription() const override;

    private:
        int getMinDamage() const;

        int getMaxDamage() const;

        double scatter_;
    };

}  // namespace lab3