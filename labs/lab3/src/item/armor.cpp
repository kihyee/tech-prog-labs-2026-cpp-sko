#include "item/armor.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace lab3 {

    Armor::Armor(std::string code, std::string name, int basePrice, double defense)
        : Item(std::move(code), std::move(name), basePrice), defense_(defense) {}

    std::unique_ptr<Item> Armor::clone() const {
        return std::make_unique<Armor>(*this);
    }

    double Armor::getDefense() const {
        double total = defense_;
        for (const Enchantment* enchantment : getEnchantments()) {
            total += enchantment->bonusDefense;
        }

        return std::min(total, MAX_DEFENSE);
    }

    const std::vector<const Enchantment*>& Armor::getPossibleEnchantments() const {
        return enchantments::FOR_ARMOR;
    }

    std::string Armor::getDescription() const {
        return "защита " + std::to_string(std::lround(getDefense() * 100)) + "%";
    }

}  // namespace lab3