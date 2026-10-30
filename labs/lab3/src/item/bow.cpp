#include "item/bow.hpp"

#include <cmath>
#include <utility>

#include "core/dice.hpp"

namespace lab3 {

    Bow::Bow(std::string code, std::string name, int basePrice, int damage, double criticalChance)
        : Weapon(std::move(code), std::move(name), basePrice, damage), criticalChance_(criticalChance) {}

    Hit Bow::rollDamage() const {
        if (Dice::getInstance().chance(criticalChance_)) {
            return {getDamage() * CRITICAL_MULTIPLIER, true};
        }

        return {getDamage(), false};
    }

    std::unique_ptr<Item> Bow::clone() const {
        return std::make_unique<Bow>(*this);
    }

    std::string Bow::getDescription() const {
        return "урон " + std::to_string(getDamage()) +
               ", шанс крита " + std::to_string(std::lround(criticalChance_ * 100)) + "%";
    }

}  // namespace lab3