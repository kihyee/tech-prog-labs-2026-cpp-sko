#include "item/sword.hpp"

#include <utility>

namespace lab3 {

    Sword::Sword(std::string code, std::string name, int basePrice, int damage)
        : Weapon(std::move(code), std::move(name), basePrice, damage) {}

    Hit Sword::rollDamage() const {
        return {getDamage(), false};
    }

    std::unique_ptr<Item> Sword::clone() const {
        // конструктор копирования Sword копирует все поля, включая поля родителей
        return std::make_unique<Sword>(*this);
    }

    std::string Sword::getDescription() const {
        return "урон " + std::to_string(getDamage());
    }

}  // namespace lab3