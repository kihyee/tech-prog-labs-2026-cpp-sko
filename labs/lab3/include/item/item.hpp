#pragma once

#include <memory>
#include <string>
#include <vector>

#include "item/enchantment.hpp"

namespace lab3 {

    class Item {
    public:
        virtual ~Item() = default;

        // каждый наследник по-своему реализует копирование;
        // unique_ptr означает, что вызывающий код становится единственным владельцем новой копии
        virtual std::unique_ptr<Item> clone() const = 0;

        // какие зачарования подходят этому предмету
        virtual const std::vector<const Enchantment*>& getPossibleEnchantments() const = 0;

        // описание характеристик предмета, например "урон 12"
        virtual std::string getDescription() const = 0;

        void enchant(const Enchantment& enchantment);

        const std::string& getCode() const;

        const std::string& getName() const;

        int getPrice() const;

        const std::vector<const Enchantment*>& getEnchantments() const;

    protected:
        Item(std::string code, std::string name, int basePrice);

        // конструктор копирования, его вызывают наследники в методе clone();
        // он защищенный, чтобы предмет нельзя было скопировать снаружи в обход clone()
        Item(const Item& source) = default;

        Item& operator=(const Item&) = delete;

    private:
        // код шаблона, из которого получен предмет
        std::string code_;
        std::string name_;
        int basePrice_;
        // при копировании предмета вектор копируется целиком, а вот указатели в нем указывают
        // на те же самые зачарования - их копировать и не нужно, они неизменяемые
        std::vector<const Enchantment*> enchantments_;
    };

}  // namespace lab3