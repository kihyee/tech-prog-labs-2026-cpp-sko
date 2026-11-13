#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <memory>
#include <vector>
#include "console_view.hpp"
#include "game/game_facade.hpp"
#include "defense/armor_handler.hpp"
#include "defense/barrier_handler.hpp"
#include "defense/evasion_handler.hpp"
#include "enemy/goblin.hpp"
#include "enemy/dragon.hpp"
#include "enemy/legendary_enemy.hpp"
#include "enemy/windfury_enemy.hpp"
#include "enemy/armored_enemy.hpp"
#include "enemy/haunted_weapon.hpp"
using namespace lab3;
namespace {
const ConsoleView VIEW;
Hero newHero(const std::string &name, const HeroClass &hc, int level, const ItemCatalog &catalog) {
    return Hero::Builder()
        .setName(name)
        .setHeroClass(hc)
        .setStarterKit(*hc.getStarterKit(catalog))
        .setLevel(level)
        .build();
}
void printHits(const std::string &title, DamageHandler &chain, int count) {
    std::cout << title << ": ";
    for (int i = 0; i < count; ++i) {
        if (i)
            std::cout << "; ";
        Damage d(30);
        chain.handle(d);
        if (d.isEvaded())
            std::cout << "уклонение";
        else if (d.getAbsorbed() > 0)
            std::cout << "поглощено " << d.getAbsorbed() << ", прошло " << d.getAmount();
        else
            std::cout << "прошло " << d.getAmount();
    }
    std::cout << "\n";
}
class EventPrinter : public GameEventListener {
  public:
    void onEvent(const GameEvent &e) override {
        std::cout << "Событие VICTORY: герой " << e.hero.getName() << "\n";
    }
};
class TempDirectory {
  public:
    std::filesystem::path path;
    TempDirectory() {
        auto prefix = std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0;; ++i) {
            path = std::filesystem::temp_directory_path() / ("lab-demo-" + prefix + "-" + std::to_string(i));
            if (std::filesystem::create_directory(path))
                break;
        }
    }
    ~TempDirectory() {
        std::error_code error;
        std::filesystem::remove_all(path, error);
    }
};
} // namespace
int main() {
    ConsoleView::setupConsole();
    std::cout << std::boolalpha;
    auto catalog = createDefaultCatalog();
    auto &dice = Dice::getInstance();
    std::cout << "===== Цепочка обязанностей =====\n";
    ArmorHandler armor(0.3);
    printHits("Броня 30%", armor, 2);
    ArmorHandler barrier(0.3);
    barrier.setNext(std::make_unique<BarrierHandler>(30));
    printHits("Броня 30% -> барьер 30", barrier, 3);
    dice.reseed(3);
    EvasionHandler chain(0.5);
    chain.setNext(std::make_unique<ArmorHandler>(0.3)).setNext(std::make_unique<BarrierHandler>(30));
    printHits("Уклонение 50% -> броня 30% -> барьер 30", chain, 3);
    std::cout << "\n===== Стратегия =====\n";
    BalancedTactic balanced;
    AggressiveTactic aggressive;
    CautiousTactic cautious;
    for (const Tactic *tactic : std::vector<const Tactic *>{&balanced, &aggressive, &cautious}) {
        auto mage = newHero("Мерлин", HeroClass::MAGE, 2, catalog);
        auto report = Crypt(catalog).explore(mage, *tactic, 9);
        std::cout << tactic->getDisplayName() << ": "
                  << (report.battle.outcome == Outcome::VICTORY ? "победа" : "поражение") << ", раундов "
                  << report.battle.events.back().round << ", у героя осталось " << mage.getHealth() << "/"
                  << mage.getMaxHealth() << " здоровья\n";
    }
    std::cout << "\n===== Декоратор =====\n";
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Goblin>());
    enemies.push_back(std::make_unique<LegendaryEnemy>(std::make_unique<Goblin>()));
    enemies.push_back(std::make_unique<WindfuryEnemy>(std::make_unique<Goblin>()));
    enemies.push_back(
        std::make_unique<LegendaryEnemy>(std::make_unique<WindfuryEnemy>(std::make_unique<Goblin>())));
    enemies.push_back(std::make_unique<ArmoredEnemy>(std::make_unique<Goblin>()));
    enemies.push_back(std::make_unique<ArmoredEnemy>(
        std::make_unique<LegendaryEnemy>(std::make_unique<WindfuryEnemy>(std::make_unique<Dragon>()))));
    for (auto &enemy : enemies) {
        dice.reseed(5);
        std::ostringstream hits;
        for (int i = 0; i < 3; ++i) {
            if (i)
                hits << ", ";
            hits << enemy->rollDamage().damage;
        }
        auto d = enemy->receiveHit(20);
        std::cout << enemy->getName() << ": удары " << hits.str() << ", награда "
                  << enemy->getExperienceReward() << " опыта; входящий урон 20 -> " << d.getAmount()
                  << ", здоровье " << enemy->getHealth() << "/" << enemy->getMaxHealth() << "\n";
    }
    std::cout << "\n===== Адаптер =====\n";
    std::shared_ptr<Weapon> bow = catalog.createWeapon(item_codes::ELVEN_BOW);
    HauntedWeapon haunted(bow);
    std::cout << "Предмет: " << VIEW.describe(*bow) << "\nВраг:    " << haunted.getName() << " ("
              << haunted.getMaxHealth() << " здоровья, награда " << haunted.getExperienceReward()
              << " опыта)\n";
    HauntedManor manor(catalog);
    auto ranger = newHero("Леголас", HeroClass::RANGER, 2, catalog);
    VIEW.printReport(manor.explore(ranger, cautious, 55), manor.getDisplayName());
    std::cout << "\n===== Наблюдатель =====\n";
    GameEventPublisher events;
    auto journal = std::make_shared<ExpeditionJournal>();
    events.subscribe(GameEventType::VICTORY, std::make_shared<AchievementTracker>());
    events.subscribe(GameEventType::VICTORY, journal);
    events.subscribe(GameEventType::DEFEAT, journal);
    events.subscribe(GameEventType::VICTORY, std::make_shared<EventPrinter>());
    auto warrior = std::make_shared<Hero>(newHero("Артур", HeroClass::WARRIOR, 1, catalog));
    auto report = Forest(catalog).explore(*warrior, 1);
    events.publish(
        {report.battle.outcome == Outcome::VICTORY ? GameEventType::VICTORY : GameEventType::DEFEAT, *warrior,
         report});
    std::cout << "Достижения героя: ";
    bool first = true;
    for (auto a : warrior->getAchievements()) {
        if (!first)
            std::cout << ", ";
        std::cout << a->displayName;
        first = false;
    }
    std::cout << "\nЗаписей в журнале: " << journal->getEntries(warrior->getName()).size() << "\n";
    TempDirectory temp;
    std::cout << "\n===== Заместитель =====\n";
    auto path = temp.path / "heroes.json";
    FileHeroRepository file(path, catalog);
    file.save(warrior);
    std::cout << "Содержимое файла:\n";
    std::ifstream input(path, std::ios::binary);
    std::cout << input.rdbuf();
    input.close();
    std::cout << "Без заместителя два поиска дают один и тот же объект: "
              << (file.findByName("Артур") == file.findByName("Артур")) << "\n";
    CachingHeroRepository cached(std::make_unique<FileHeroRepository>(path, catalog));
    auto h = cached.findByName("Артур");
    std::cout << "С заместителем два поиска дают один и тот же объект: " << (h == cached.findByName("Артур"))
              << "\n";
    h->addGold(100);
    cached.save(h);
    std::cout << "После сохранения через заместитель золото героя в файле: "
              << file.findByName("Артур")->getGold() << "\n";
    std::cout << "\n===== Фасад =====\n";
    GameFacade game(temp.path / "game.json");
    game.createHero("Гэндальф", "mage");
    dice.reseed(11);
    auto expedition = game.explore("Гэндальф", "forest", "cautious");
    std::cout << "Экспедиция через фасад: "
              << VIEW.summarize(expedition, game.getLocation(expedition.locationCode).getDisplayName(),
                                game.getTactic(expedition.tacticCode).getDisplayName())
              << "\n";
    VIEW.printHero(*game.getHero("Гэндальф"));
}