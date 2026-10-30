#include "item/weapon.hpp"

#include <utility>

namespace lab3 {

    Weapon::Weapon(std::string code, std::string name, int basePrice, int damage)
        : Item(std::move(code), std::move(name), basePrice), damage_(damage) {}

    int Weapon::getDamage() const {
        int total = damage_;
        for (const Enchantment* enchantment : getEnchantments()) {
            total += enchantment->bonusDamage;
        }

        return total;
    }

    const std::vector<const Enchantment*>& Weapon::getPossibleEnchantments() const {
        return enchantments::FOR_WEAPONS;
    }

}  // namespace lab3