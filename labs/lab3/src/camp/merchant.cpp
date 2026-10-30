#include "camp/merchant.hpp"

#include <algorithm>
#include <utility>

#include "core/unknown_code_error.hpp"

namespace lab3 {

    Merchant::Merchant(const ItemCatalog& catalog, std::vector<std::string> assortment)
        : catalog_(catalog), assortment_(std::move(assortment)) {}

    std::vector<std::unique_ptr<Item>> Merchant::getShowcase() const {
        std::vector<std::unique_ptr<Item>> showcase;
        for (const std::string& code : assortment_) {
            showcase.push_back(catalog_.create(code));
        }

        return showcase;
    }

    std::shared_ptr<Item> Merchant::buy(Hero& hero, const std::string& code) const {
        if (std::find(assortment_.begin(), assortment_.end(), code) == assortment_.end()) {
            throw UnknownCodeError("Товар", code);
        }

        // покупатель получает собственную копию предмета из каталога
        std::shared_ptr<Item> item = catalog_.create(code);
        hero.spendGold(item->getPrice());
        hero.addItem(item);
        return item;
    }

    int Merchant::sell(Hero& hero, const std::shared_ptr<Item>& item) const {
        int price = getSellPrice(*item);
        hero.removeItem(item);
        hero.addGold(price);
        return price;
    }

    int Merchant::getSellPrice(const Item& item) const {
        return item.getPrice() * SELL_PRICE_PERCENT / 100;
    }

}  // namespace lab3