#include <iostream>
#include <stdexcept>

#include "console_view.hpp"
#include "core/dice.hpp"
#include "hero/hero.hpp"
#include "hero/hero_class.hpp"
#include "item/default_catalog.hpp"
#include "item/enchantment.hpp"
#include "item/item_catalog.hpp"
#include "world/crypt.hpp"
#include "world/forest.hpp"

using namespace lab3;

int main() {
    ConsoleView::setupConsole();
    std::cout << std::boolalpha;

    ItemCatalog catalog = createDefaultCatalog();
    ConsoleView view;

    std::cout << "===== Одиночка =====\n";
    Dice& first = Dice::getInstance();
    Dice& second = Dice::getInstance();
    std::cout << "Dice::getInstance() возвращает один и тот же объект: " << (&first == &second) << "\n";

    std::cout << "\n===== Прототип =====\n";
    auto plainSword = catalog.create(item_codes::IRON_SWORD);
    auto fierySword = catalog.create(item_codes::IRON_SWORD);
    fierySword->enchant(enchantments::FIERY);
    std::cout << "Первая копия:        " << view.describe(*plainSword) << "\n";
    std::cout << "Вторая копия:        " << view.describe(*fierySword) << "\n";
    std::cout << "Новая копия шаблона: " << view.describe(*catalog.create(item_codes::IRON_SWORD)) << "\n";
    std::cout << "Копии - разные объекты: " << (plainSword.get() != fierySword.get()) << "\n";

    std::cout << "\n===== Абстрактная фабрика =====\n";
    for (const HeroClass* heroClass : HeroClass::values()) {
        auto kit = heroClass->getStarterKit(catalog);
        std::cout << heroClass->getDisplayName() << ": " << view.describe(*kit->createWeapon()) << ", "
                  << view.describe(*kit->createArmor()) << "\n";
    }

    std::cout << "\n===== Строитель =====\n";
    Hero hero = Hero::Builder()
        .setName("Артур")
        .setHeroClass(HeroClass::WARRIOR)
        .setStarterKit(*HeroClass::WARRIOR.getStarterKit(catalog))
        .setLevel(3)
        .build();
    view.printHero(hero);
    try {
        Hero::Builder()
            .setHeroClass(HeroClass::MAGE)
            .setStarterKit(*HeroClass::MAGE.getStarterKit(catalog))
            .build();
    } catch (const std::invalid_argument& error) {
        std::cout << "Герой без имени не создается: " << error.what() << "\n";
    }
    try {
        Hero::Builder().setName("Мерлин").build();
    } catch (const std::invalid_argument& error) {
        std::cout << "Герой без класса не создается: " << error.what() << "\n";
    }

    std::cout << "\n===== Фабричный метод =====\n";
    Forest forest(catalog);
    Crypt crypt(catalog);
    view.printReport(forest.explore(hero, 7), forest.getDisplayName());
    std::cout << "\n";
    view.printReport(crypt.explore(hero, 7), crypt.getDisplayName());


    return 0;
}