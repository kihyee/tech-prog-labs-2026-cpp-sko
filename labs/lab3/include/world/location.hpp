#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "core/dice.hpp"
#include "enemy/enemy.hpp"
#include "hero/hero.hpp"
#include "item/item_catalog.hpp"
#include "world/expedition_report.hpp"
#include "world/rewards.hpp"

namespace lab3 {

    class Location {
    public:
        virtual ~Location() = default;

        ExpeditionReport explore(Hero& hero) const;

        // бизнес-логика, общая для всех локаций:
        // герой встречает врага, сражается с ним и получает награду, если победил
        ExpeditionReport explore(Hero& hero, std::uint32_t seed) const;

        const std::string& getCode() const;

        const std::string& getDisplayName() const;

        int getRecommendedLevel() const;

    protected:
        Location(std::string code, std::string displayName, int recommendedLevel, const ItemCatalog& catalog);

        // создание врага делегируется подклассам для повышения гибкости
        virtual std::unique_ptr<Enemy> createEnemy() const = 0;

        // коды предметов из каталога, которые можно найти в локации
        virtual const std::vector<std::string>& getLootTable() const = 0;

    private:
        static constexpr double LOOT_CHANCE = 0.6;
        static constexpr double ENCHANT_CHANCE = 0.3;

        Rewards reward(Hero& hero, const Enemy& enemy, Dice& dice) const;

        std::shared_ptr<Item> rollLoot(Dice& dice) const;

        // проигравший герой теряет половину золота
        Rewards punish(Hero& hero) const;

        std::string code_;
        std::string displayName_;
        int recommendedLevel_;
        const ItemCatalog& catalog_;
    };

}  // namespace lab3