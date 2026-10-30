#pragma once

#include <memory>

#include "item/armor.hpp"
#include "item/weapon.hpp"

namespace lab3 {

    // Абстрактная фабрика: стартовый набор снаряжения
    class StarterKitFactory {
    public:
        virtual ~StarterKitFactory() = default;

        // возвращает некое оружие
        virtual std::unique_ptr<Weapon> createWeapon() const = 0;

        // возвращает некую броню
        virtual std::unique_ptr<Armor> createArmor() const = 0;
    };

}  // namespace lab3