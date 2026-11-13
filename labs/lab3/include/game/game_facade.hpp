#pragma once
#include "camp/merchant.hpp"
#include "world/location_registry.hpp"
#include "world/forest.hpp"
#include "world/haunted_manor.hpp"
#include "world/crypt.hpp"
#include "world/dragon_lair.hpp"
#include "tactic/balanced_tactic.hpp"
#include "tactic/aggressive_tactic.hpp"
#include "tactic/cautious_tactic.hpp"
#include "storage/file_hero_repository.hpp"
#include "storage/caching_hero_repository.hpp"
#include "event/game_event_publisher.hpp"
#include "progress/achievement_tracker.hpp"
#include "progress/expedition_journal.hpp"
#include "item/default_catalog.hpp"

namespace lab3 {
class GameFacade {
    ItemCatalog catalog_ = createDefaultCatalog();
    LocationRegistry locations_;
    std::vector<std::unique_ptr<Tactic>> tactics_;
    Merchant merchant_;
    CachingHeroRepository heroes_;
    GameEventPublisher events_;
    std::shared_ptr<ExpeditionJournal> journal_ = std::make_shared<ExpeditionJournal>();
    static std::vector<std::unique_ptr<Location>> locations(const ItemCatalog &catalog) {
        std::vector<std::unique_ptr<Location>> result;
        result.push_back(std::make_unique<Forest>(catalog));
        result.push_back(std::make_unique<HauntedManor>(catalog));
        result.push_back(std::make_unique<Crypt>(catalog));
        result.push_back(std::make_unique<DragonLair>(catalog));
        return result;
    }

  public:
    explicit GameFacade(const std::filesystem::path &file)
        : locations_(locations(catalog_)),
          merchant_(catalog_, {item_codes::IRON_SWORD, item_codes::ELVEN_BOW, item_codes::EMBER_STAFF,
                               item_codes::CHAINMAIL, item_codes::PLATE_ARMOR}),
          heroes_(std::make_unique<FileHeroRepository>(file, catalog_)) {
        tactics_.push_back(std::make_unique<BalancedTactic>());
        tactics_.push_back(std::make_unique<AggressiveTactic>());
        tactics_.push_back(std::make_unique<CautiousTactic>());
        auto achievements = std::make_shared<AchievementTracker>();
        events_.subscribe(GameEventType::VICTORY, achievements);
        events_.subscribe(GameEventType::LEVEL_UP, achievements);
        events_.subscribe(GameEventType::VICTORY, journal_);
        events_.subscribe(GameEventType::DEFEAT, journal_);
    }
    GameFacade(const GameFacade &) = delete;
    GameFacade &operator=(const GameFacade &) = delete;
    GameFacade(GameFacade &&) = delete;
    GameFacade &operator=(GameFacade &&) = delete;
    const std::vector<const HeroClass *> &getHeroClasses() const {
        return HeroClass::values();
    }
    std::vector<std::unique_ptr<Item>> getStarterKit(const std::string &code) const {
        auto kit = HeroClass::byCode(code).getStarterKit(catalog_);
        std::vector<std::unique_ptr<Item>> result;
        result.push_back(kit->createWeapon());
        result.push_back(kit->createArmor());
        return result;
    }
    auto getLocations() const {
        return locations_.getAll();
    }
    const Location &getLocation(const std::string &code) const {
        return locations_.get(code);
    }
    std::vector<const Tactic *> getTactics() const {
        std::vector<const Tactic *> result;
        for (auto &t : tactics_)
            result.push_back(t.get());
        return result;
    }
    const Tactic &getTactic(const std::string &code) const {
        for (auto &t : tactics_)
            if (t->getCode() == code)
                return *t;
        throw UnknownCodeError("Тактика", code);
    }
    auto getShowcase() const {
        return merchant_.getShowcase();
    }
    int getSellPrice(const Item &item) const {
        return merchant_.getSellPrice(item);
    }
    auto getHeroes() {
        return heroes_.findAll();
    }
    std::shared_ptr<Hero> getHero(const std::string &name) {
        auto h = heroes_.findByName(name);
        if (!h)
            throw std::invalid_argument("Героя с именем " + name + " нет");
        return h;
    }
    std::shared_ptr<Hero> createHero(const std::string &name, const std::string &code) {
        if (heroes_.findByName(name))
            throw std::invalid_argument("Герой с именем " + name + " уже есть");
        auto &hc = HeroClass::byCode(code);
        auto h = std::make_shared<Hero>(Hero::Builder()
                                            .setName(name)
                                            .setHeroClass(hc)
                                            .setStarterKit(*hc.getStarterKit(catalog_))
                                            .build());
        heroes_.save(h);
        return h;
    }
    ExpeditionReport explore(const std::string &name, const std::string &locationCode,
                             const std::string &tacticCode) {
        auto h = getHero(name);
        auto report = getLocation(locationCode).explore(*h, getTactic(tacticCode));
        auto result =
            report.battle.outcome == Outcome::VICTORY ? GameEventType::VICTORY : GameEventType::DEFEAT;
        events_.publish({result, *h, report});
        if (report.rewards.levelsGained > 0)
            events_.publish({GameEventType::LEVEL_UP, *h, report});
        heroes_.save(h);
        return report;
    }
    std::shared_ptr<Item> equip(const std::string &name, std::size_t index) {
        auto h = getHero(name);
        auto item = h->getInventory().at(index);
        h->equip(item);
        heroes_.save(h);
        return item;
    }
    std::shared_ptr<Item> buy(const std::string &name, const std::string &code) {
        auto h = getHero(name);
        auto item = merchant_.buy(*h, code);
        heroes_.save(h);
        return item;
    }
    int sell(const std::string &name, std::size_t index) {
        auto h = getHero(name);
        int price = merchant_.sell(*h, h->getInventory().at(index));
        heroes_.save(h);
        return price;
    }
    auto getJournal(const std::string &name) const {
        return journal_->getEntries(name);
    }
};
} // namespace lab3