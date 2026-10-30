#include "console_view.hpp"

#include <iostream>

#include "combat/event_type.hpp"
#include "combat/outcome.hpp"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace lab3 {

void ConsoleView::setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

std::string ConsoleView::describe(const Item& item) const {
    std::string description = item.getName();

    const auto& enchantments = item.getEnchantments();
    if (!enchantments.empty()) {
        description += " [";
        for (std::size_t i = 0; i < enchantments.size(); i++) {
            if (i > 0) {
                description += ", ";
            }
            description += enchantments[i]->name;
        }
        description += "]";
    }

    return description + " (" + item.getDescription() + ")";
}

void ConsoleView::printHero(const Hero& hero) const {
    std::cout << hero.getName() << ", " << hero.getHeroClass().getDisplayName() << " " << hero.getLevel()
              << " ур. | здоровье " << hero.getMaxHealth()
              << " | опыт " << hero.getExperience() << "/" << hero.getExperienceToNextLevel()
              << " | золото " << hero.getGold() << "\n";
    std::cout << "  Оружие: " << describe(hero.getWeapon()) << "\n";
    std::cout << "  Броня:  " << describe(hero.getArmor()) << "\n";
}

void ConsoleView::printReport(const ExpeditionReport& report, const std::string& locationName) const {
    const BattleReport& battle = report.battle;
    std::cout << "=== " << locationName << " (сид " << report.seed << ") ===\n";
    std::cout << battle.hero.name << " встречает врага: " << battle.enemy.name
              << " (" << battle.enemy.maxHealth << " здоровья)\n";

    for (const BattleEvent& event : battle.events) {
        printEvent(event, battle);
    }

    printRewards(battle, report.rewards);
}

void ConsoleView::printEvent(const BattleEvent& event, const BattleReport& battle) const {
    const Participant& source = participant(event.source, battle);
    const Participant& target = participant(event.target, battle);

    switch (event.type) {
        case EventType::HIT:
            std::cout << "[раунд " << event.round << "] " << source.name << " -> " << target.name << ": "
                      << event.amount << " урона, осталось "
                      << event.targetHealthAfter << "/" << target.maxHealth << "\n";
            break;
        case EventType::CRITICAL_HIT:
            std::cout << "[раунд " << event.round << "] " << source.name << " -> " << target.name << ": КРИТ! "
                      << event.amount << " урона, осталось "
                      << event.targetHealthAfter << "/" << target.maxHealth << "\n";
            break;
        case EventType::DEATH:
            std::cout << target.name << " повержен!\n";
            break;
    }
}

void ConsoleView::printRewards(const BattleReport& battle, const Rewards& rewards) const {
    if (battle.outcome == Outcome::DEFEAT) {
        std::cout << "Поражение... " << battle.hero.name << " едва уносит ноги и теряет "
                  << -rewards.gold << " золота\n";
        return;
    }

    std::cout << "Победа! +" << rewards.experience << " опыта, +" << rewards.gold << " золота\n";
    if (rewards.loot != nullptr) {
        std::cout << "Добыча: " << describe(*rewards.loot) << "\n";
    }
    if (rewards.levelsGained > 0) {
        std::cout << "Новый уровень!\n";
    }
}

const Participant& ConsoleView::participant(Side side, const BattleReport& battle) const {
    return side == Side::HERO ? battle.hero : battle.enemy;
}

}  // namespace lab3