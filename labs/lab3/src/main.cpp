#include "game/game_facade.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "camp/merchant.hpp"
#include "combat/outcome.hpp"
#include "console_view.hpp"
#include "hero/hero.hpp"
#include "hero/hero_class.hpp"
#include "item/default_catalog.hpp"
#include "item/item_catalog.hpp"
#include "world/crypt.hpp"
#include "world/dragon_lair.hpp"
#include "world/forest.hpp"
#include "world/location_registry.hpp"

using namespace lab3;

namespace {

const ConsoleView VIEW;

// читает строку без пробелов по краям; если ввод закончился, завершает программу
std::string readLine() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::exit(0);
    }

    std::size_t begin = line.find_first_not_of(" \t\r");
    if (begin == std::string::npos) {
        return "";
    }
    std::size_t end = line.find_last_not_of(" \t\r");
    return line.substr(begin, end - begin + 1);
}

// читает номер варианта от 1 до count, возвращает индекс или -1, если ввели что-то другое
int readChoice(std::size_t count) {
    std::string line = readLine();
    try {
        int choice = std::stoi(line);
        if (choice >= 1 && static_cast<std::size_t>(choice) <= count) {
            return choice - 1;
        }
    } catch (const std::exception &) {
        // некорректный ввод обрабатываем так же, как отказ от выбора
    }

    return -1;
}

std::shared_ptr<Hero> createHero(GameFacade &game) {
    std::cout << "Создайте своего героя!\n";
    while (true) {
        std::cout << "Выберите класс:\n";
        const auto &heroClasses = HeroClass::values();
        for (std::size_t i = 0; i < heroClasses.size(); i++) {
            auto kit = game.getStarterKit(heroClasses[i]->getCode());
            std::cout << i + 1 << " - " << heroClasses[i]->getDisplayName() << " (здоровье "
                      << heroClasses[i]->getBaseHealth() << "): " << VIEW.describe(*kit[0]) << ", "
                      << VIEW.describe(*kit[1]) << "\n";
        }
        int classIndex = readChoice(heroClasses.size());
        if (classIndex < 0) {
            continue;
        }
        const HeroClass &heroClass = *heroClasses[static_cast<std::size_t>(classIndex)];

        std::cout << "Введите имя:\n";
        std::string name = readLine();

        try {
            return game.createHero(name, heroClass.getCode());
        } catch (const std::invalid_argument &error) {
            std::cout << "Не получилось создать героя: " << error.what() << "\n";
        }
    }
}

std::shared_ptr<Hero> chooseHero(GameFacade &game) {
    auto heroes = game.getHeroes();
    if (heroes.empty())
        return createHero(game);
    std::cout << "Выберите сохраненного героя (0 - создать нового):\n";
    for (std::size_t i = 0; i < heroes.size(); ++i)
        std::cout << i + 1 << " - " << heroes[i]->getName() << ", "
                  << heroes[i]->getHeroClass().getDisplayName() << " " << heroes[i]->getLevel() << " ур.\n";
    int index = readChoice(heroes.size());
    return index >= 0 ? heroes[static_cast<std::size_t>(index)] : createHero(game);
}

void goOnExpedition(Hero &hero, GameFacade &game) {
    std::vector<const Location *> all = game.getLocations();
    std::cout << "Куда отправимся?\n";
    for (std::size_t i = 0; i < all.size(); i++) {
        std::cout << i + 1 << " - " << all[i]->getDisplayName() << " (рекомендуемый уровень "
                  << all[i]->getRecommendedLevel() << ")\n";
    }
    int index = readChoice(all.size());
    if (index < 0) {
        return;
    }

    const Location &location = *all[static_cast<std::size_t>(index)];
    std::cout << "Выберите тактику:\n";
    auto tactics = game.getTactics();
    for (std::size_t i = 0; i < tactics.size(); ++i)
        std::cout << i + 1 << " - " << tactics[i]->getDisplayName() << ": " << tactics[i]->getDescription()
                  << "\n";
    int tacticIndex = readChoice(tactics.size());
    if (tacticIndex < 0)
        return;
    ExpeditionReport report = game.explore(hero.getName(), location.getCode(),
                                           tactics[static_cast<std::size_t>(tacticIndex)]->getCode());
    std::cout << "\n";
    VIEW.printReport(report, location.getDisplayName());

    if (report.battle.outcome == Outcome::VICTORY && report.battle.enemy.code == "dragon") {
        std::cout << "\nДракон повержен! Барды еще долго будут петь о подвиге героя по имени "
                  << hero.getName() << ".\n";
    }
}

void printItems(const std::vector<std::shared_ptr<Item>> &items) {
    for (std::size_t i = 0; i < items.size(); i++) {
        std::cout << i + 1 << " - " << VIEW.describe(*items[i]) << "\n";
    }
}

void manageEquipment(Hero &hero, GameFacade &game) {
    // копируем список: после equip инвентарь героя изменится
    std::vector<std::shared_ptr<Item>> inventory = hero.getInventory();
    if (inventory.empty()) {
        std::cout << "Инвентарь пуст\n";
        return;
    }

    std::cout << "Что экипировать? (0 - назад)\n";
    printItems(inventory);
    int index = readChoice(inventory.size());
    if (index < 0) {
        return;
    }

    const auto &item = inventory[static_cast<std::size_t>(index)];
    game.equip(hero.getName(), static_cast<std::size_t>(index));
    std::cout << "Экипировано: " << VIEW.describe(*item) << "\n";
}

void buy(Hero &hero, GameFacade &game) {
    std::vector<std::unique_ptr<Item>> showcase = game.getShowcase();
    for (std::size_t i = 0; i < showcase.size(); i++) {
        std::cout << i + 1 << " - " << VIEW.describe(*showcase[i]) << ": " << showcase[i]->getPrice()
                  << " золота\n";
    }
    int index = readChoice(showcase.size());
    if (index < 0) {
        return;
    }

    try {
        auto item = game.buy(hero.getName(), showcase[static_cast<std::size_t>(index)]->getCode());
        std::cout << "Куплено: " << VIEW.describe(*item) << "\n";
    } catch (const std::runtime_error &error) {
        std::cout << error.what() << "\n";
    }
}

void sell(Hero &hero, GameFacade &game) {
    std::vector<std::shared_ptr<Item>> inventory = hero.getInventory();
    if (inventory.empty()) {
        std::cout << "Продавать нечего (экипированные предметы продать нельзя)\n";
        return;
    }

    for (std::size_t i = 0; i < inventory.size(); i++) {
        std::cout << i + 1 << " - " << VIEW.describe(*inventory[i]) << ": "
                  << game.getSellPrice(*inventory[i]) << " золота\n";
    }
    int index = readChoice(inventory.size());
    if (index < 0) {
        return;
    }

    const auto &item = inventory[static_cast<std::size_t>(index)];
    int price = game.sell(hero.getName(), static_cast<std::size_t>(index));
    std::cout << "Продано: " << item->getName() << " за " << price << " золота\n";
}

void visitMerchant(Hero &hero, GameFacade &game) {
    std::cout << "Торговец: \"Чего желаешь?\" (золото: " << hero.getGold() << ")\n";
    std::cout << "1 - купить, 2 - продать, 0 - назад\n";
    std::string choice = readLine();
    if (choice == "1") {
        buy(hero, game);
    } else if (choice == "2") {
        sell(hero, game);
    }
}

} // namespace

int main() try {
    ConsoleView::setupConsole();

    std::filesystem::path saveFile = std::filesystem::path("saves") / "heroes.json";
    auto savePath = std::filesystem::absolute(saveFile).u8string();
    std::cout << "Файл сохранения: " << std::string(savePath.begin(), savePath.end()) << "\n";
    GameFacade game(saveFile);
    auto selectedHero = chooseHero(game);
    Hero &hero = *selectedHero;
    std::cout << hero.getName() << " разбивает лагерь на опушке мистического леса.\n";

    while (true) {
        std::cout << "\n";
        VIEW.printHero(hero);
        std::cout
            << "1 - отправиться в экспедицию, 2 - снаряжение, 3 - торговец, 4 - журнал, 0 - выйти из игры\n";
        std::string choice = readLine();
        if (choice == "1") {
            goOnExpedition(hero, game);
        } else if (choice == "2") {
            manageEquipment(hero, game);
        } else if (choice == "3") {
            visitMerchant(hero, game);
        } else if (choice == "4") {
            for (auto &report : game.getJournal(hero.getName()))
                std::cout << VIEW.summarize(report, game.getLocation(report.locationCode).getDisplayName(),
                                            game.getTactic(report.tacticCode).getDisplayName())
                          << "\n";
        } else if (choice == "0") {
            return 0;
        } else {
            std::cout << "Такого варианта нет\n";
        }
    }
}
catch (const std::exception &error) {
    std::cerr << error.what() << "\n";
    return 1;
}