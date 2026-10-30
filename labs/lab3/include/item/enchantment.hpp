#pragma once

#include <string>
#include <vector>

namespace lab3 {

    // зачарование неизменяемо: все его поля константные и не меняются после создания,
    // поэтому одно и то же зачарование можно безопасно повесить на несколько предметов
    struct Enchantment {
        const std::string code;
        const std::string name;
        const int bonusDamage;
        const double bonusDefense;
        const int bonusPrice;
    };

    namespace enchantments {

        inline const Enchantment SHARP{"sharp", "Острое", 3, 0, 20};
        inline const Enchantment FIERY{"fiery", "Огненное", 6, 0, 50};
        inline const Enchantment STURDY{"sturdy", "Прочное", 0, 0.05, 20};
        inline const Enchantment WARDING{"warding", "Охранное", 0, 0.10, 50};

        inline const std::vector<const Enchantment*> FOR_WEAPONS{&SHARP, &FIERY};
        inline const std::vector<const Enchantment*> FOR_ARMOR{&STURDY, &WARDING};

    }  // namespace enchantments

}  // namespace lab3