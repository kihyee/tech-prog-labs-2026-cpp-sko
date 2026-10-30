#pragma once

#include <string>
#include <vector>

#include "combat/hit.hpp"
#include "item/item.hpp"

namespace lab3 {

    class Weapon : public Item {
    public:
        // как именно оружие наносит урон, решают наследники
        virtual Hit rollDamage() const = 0;

        // урон с учетом зачарований
        int getDamage() const;

        const std::vector<const Enchantment*>& getPossibleEnchantments() const override;

    protected:
        Weapon(std::string code, std::string name, int basePrice, int damage);

        Weapon(const Weapon& source) = default;

    private:
        int damage_;
    };

}  // namespace lab3