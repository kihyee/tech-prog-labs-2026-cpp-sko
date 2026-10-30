#include "item/item.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace lab3 {

    Item::Item(std::string code, std::string name, int basePrice)
        : code_(std::move(code)), name_(std::move(name)), basePrice_(basePrice) {}

    void Item::enchant(const Enchantment& enchantment) {
        const auto& possible = getPossibleEnchantments();
        if (std::find(possible.begin(), possible.end(), &enchantment) == possible.end()) {
            throw std::invalid_argument(
                "Зачарование '" + enchantment.name + "' не подходит для предмета '" + name_ + "'"
            );
        }

        enchantments_.push_back(&enchantment);
    }

    const std::string& Item::getCode() const {
        return code_;
    }

    const std::string& Item::getName() const {
        return name_;
    }

    int Item::getPrice() const {
        int price = basePrice_;
        for (const Enchantment* enchantment : enchantments_) {
            price += enchantment->bonusPrice;
        }

        return price;
    }

    const std::vector<const Enchantment*>& Item::getEnchantments() const {
        return enchantments_;
    }

}  // namespace lab3