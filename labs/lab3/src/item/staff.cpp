#include "item/staff.hpp"

#include <cmath>
#include <utility>

#include "core/dice.hpp"

namespace lab3 {

    Staff::Staff(std::string code, std::string name, int basePrice, int damage, double scatter)
        : Weapon(std::move(code), std::move(name), basePrice, damage), scatter_(scatter) {}

    Hit Staff::rollDamage() const {
        return {Dice::getInstance().roll(getMinDamage(), getMaxDamage()), false};
    }

    std::unique_ptr<Item> Staff::clone() const {
        return std::make_unique<Staff>(*this);
    }

    std::string Staff::getDescription() const {
        return "урон " + std::to_string(getMinDamage()) + "-" + std::to_string(getMaxDamage());
    }

    int Staff::getMinDamage() const {
        return static_cast<int>(std::lround(getDamage() * (1 - scatter_)));
    }

    int Staff::getMaxDamage() const {
        return static_cast<int>(std::lround(getDamage() * (1 + scatter_)));
    }

}  // namespace lab3