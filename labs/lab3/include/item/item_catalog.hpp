#pragma once

#include <memory>
#include <string>
#include <vector>

#include "item/armor.hpp"
#include "item/item.hpp"
#include "item/weapon.hpp"

namespace lab3 {

    // каталог хранит шаблоны предметов, а наружу отдает только их копии
    class ItemCatalog {
    public:
        // каталог становится владельцем шаблона
        void add(std::unique_ptr<Item> prototype);

        // каталог не знает, какой конкретно класс у шаблона - копию создает сам шаблон
        std::unique_ptr<Item> create(const std::string& code) const;

        std::unique_ptr<Weapon> createWeapon(const std::string& code) const;

        std::unique_ptr<Armor> createArmor(const std::string& code) const;

        std::vector<std::string> getCodes() const;

    private:
        // шаблоны хранятся в порядке добавления, предметов немного, поэтому ищем простым перебором
        std::vector<std::unique_ptr<Item>> prototypes_;
    };

}  // namespace lab3