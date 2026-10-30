#pragma once

#include <memory>
#include <string>
#include <vector>

#include "hero/hero.hpp"
#include "item/item.hpp"
#include "item/item_catalog.hpp"

namespace lab3 {

    class Merchant {
    public:
        Merchant(const ItemCatalog& catalog, std::vector<std::string> assortment);

        // образцы товаров, чтобы показать их покупателю
        std::vector<std::unique_ptr<Item>> getShowcase() const;

        std::shared_ptr<Item> buy(Hero& hero, const std::string& code) const;

        int sell(Hero& hero, const std::shared_ptr<Item>& item) const;

        int getSellPrice(const Item& item) const;

    private:
        static constexpr int SELL_PRICE_PERCENT = 50;

        const ItemCatalog& catalog_;
        std::vector<std::string> assortment_;
    };

}  // namespace lab3