#pragma once

#include <memory>
#include <string>

#include "item/weapon.hpp"

namespace lab3 {

    class Sword : public Weapon {
    public:
        Sword(std::string code, std::string name, int basePrice, int damage);

        Hit rollDamage() const override;

        std::unique_ptr<Item> clone() const override;

        std::string getDescription() const override;
    };

}  // namespace lab3