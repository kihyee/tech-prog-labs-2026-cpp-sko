#pragma once

#include <memory>
#include <string>
#include <vector>

#include "item/item.hpp"

namespace lab3 {

    // броня поглощает долю входящего урона
    class Armor : public Item {
    public:
        Armor(std::string code, std::string name, int basePrice, double defense);

        std::unique_ptr<Item> clone() const override;

        // доля поглощаемого урона с учетом зачарований
        double getDefense() const;

        const std::vector<const Enchantment*>& getPossibleEnchantments() const override;

        std::string getDescription() const override;

    private:
        // больше этой доли урона никакая броня не поглощает
        static constexpr double MAX_DEFENSE = 0.75;

        double defense_;
    };

}  // namespace lab3