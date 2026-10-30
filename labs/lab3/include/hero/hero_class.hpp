#pragma once

#include <memory>
#include <string>
#include <vector>

#include "item/item_catalog.hpp"
#include "kit/starter_kit_factory.hpp"

namespace lab3 {

    // в C++ перечисление (enum) не может хранить данные, поэтому классы героя - это
    // набор заранее созданных константных объектов, создать новые снаружи нельзя
    class HeroClass {
    public:
        static const HeroClass WARRIOR;
        static const HeroClass RANGER;
        static const HeroClass MAGE;

        // все классы героя по порядку
        static const std::vector<const HeroClass*>& values();

        static const HeroClass& byCode(const std::string& code);

        // каждый класс сам знает свою фабрику стартового снаряжения
        std::unique_ptr<StarterKitFactory> getStarterKit(const ItemCatalog& catalog) const;

        const std::string& getCode() const;

        const std::string& getDisplayName() const;

        int getBaseHealth() const;

    private:
        // указатель на функцию, которая создает фабрику стартового снаряжения
        using StarterKitCreator = std::unique_ptr<StarterKitFactory> (*)(const ItemCatalog&);

        HeroClass(std::string code, std::string displayName, int baseHealth, StarterKitCreator starterKit);

        std::string code_;
        std::string displayName_;
        int baseHealth_;
        StarterKitCreator starterKit_;
    };

}  // namespace lab3