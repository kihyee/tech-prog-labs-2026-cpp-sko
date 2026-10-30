#include "world/location.hpp"

#include <utility>

#include "combat/battle.hpp"

namespace lab3 {

Location::Location(std::string code, std::string displayName, int recommendedLevel, const ItemCatalog& catalog)
    : code_(std::move(code)), displayName_(std::move(displayName)), recommendedLevel_(recommendedLevel), catalog_(catalog) {}

ExpeditionReport Location::explore(Hero& hero) const {
    return explore(hero, Dice::getInstance().nextSeed());
}

ExpeditionReport Location::explore(Hero& hero, std::uint32_t seed) const {
    Dice& dice = Dice::getInstance();
    dice.reseed(seed);

    hero.restoreHealth();
    std::unique_ptr<Enemy> enemy = createEnemy();
    BattleReport battle = Battle(hero, *enemy).run();

    Rewards rewards = battle.outcome == Outcome::VICTORY
        ? reward(hero, *enemy, dice)
        : punish(hero);

    return {seed, code_, battle, rewards};
}

Rewards Location::reward(Hero& hero, const Enemy& enemy, Dice& dice) const {
    int experience = enemy.getExperienceReward();
    int gold = enemy.rollGoldReward();
    std::shared_ptr<Item> loot = rollLoot(dice);

    int levelsGained = hero.gainExperience(experience);
    hero.addGold(gold);
    if (loot != nullptr) {
        hero.addItem(loot);
    }

    return {experience, gold, loot, levelsGained};
}

std::shared_ptr<Item> Location::rollLoot(Dice& dice) const {
    if (!dice.chance(LOOT_CHANCE)) {
        return nullptr;
    }

    // добыча - это копия шаблона из каталога, ее можно менять, не боясь испортить шаблон
    std::shared_ptr<Item> loot = catalog_.create(dice.pick(getLootTable()));
    if (dice.chance(ENCHANT_CHANCE)) {
        loot->enchant(*dice.pick(loot->getPossibleEnchantments()));
    }

    return loot;
}

Rewards Location::punish(Hero& hero) const {
    int lostGold = hero.getGold() / 2;
    hero.spendGold(lostGold);
    return {0, -lostGold, nullptr, 0};
}

const std::string& Location::getCode() const {
    return code_;
}

const std::string& Location::getDisplayName() const {
    return displayName_;
}

int Location::getRecommendedLevel() const {
    return recommendedLevel_;
}

}  // namespace lab3