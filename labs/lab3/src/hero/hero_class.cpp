#include "defense/armor_handler.hpp"
#include "defense/barrier_handler.hpp"
#include "defense/evasion_handler.hpp"
#include "hero/hero_class.hpp"

#include <utility>

#include "core/unknown_code_error.hpp"
#include "kit/mage_kit_factory.hpp"
#include "kit/ranger_kit_factory.hpp"
#include "kit/warrior_kit_factory.hpp"

namespace lab3 {

// лямбда без захвата превращается в обычный указатель на функцию
const HeroClass HeroClass::WARRIOR("warrior", "Воин", 120, [](const ItemCatalog &catalog) {
    return std::unique_ptr<StarterKitFactory>(std::make_unique<WarriorKitFactory>(catalog));
});

const HeroClass HeroClass::RANGER("ranger", "Следопыт", 100, [](const ItemCatalog &catalog) {
    return std::unique_ptr<StarterKitFactory>(std::make_unique<RangerKitFactory>(catalog));
});

const HeroClass HeroClass::MAGE("mage", "Маг", 85, [](const ItemCatalog &catalog) {
    return std::unique_ptr<StarterKitFactory>(std::make_unique<MageKitFactory>(catalog));
});

HeroClass::HeroClass(std::string code, std::string displayName, int baseHealth, StarterKitCreator starterKit)
    : code_(std::move(code)), displayName_(std::move(displayName)), baseHealth_(baseHealth),
      starterKit_(starterKit) {}

const std::vector<const HeroClass *> &HeroClass::values() {
    static const std::vector<const HeroClass *> all{&WARRIOR, &RANGER, &MAGE};
    return all;
}

const HeroClass &HeroClass::byCode(const std::string &code) {
    for (const HeroClass *heroClass : values()) {
        if (heroClass->code_ == code) {
            return *heroClass;
        }
    }

    throw UnknownCodeError("Класс героя", code);
}

std::unique_ptr<StarterKitFactory> HeroClass::getStarterKit(const ItemCatalog &catalog) const {
    return starterKit_(catalog);
}

const std::string &HeroClass::getCode() const {
    return code_;
}

const std::string &HeroClass::getDisplayName() const {
    return displayName_;
}

int HeroClass::getBaseHealth() const {
    return baseHealth_;
}

std::unique_ptr<DamageHandler> HeroClass::createDefense(const Armor &armor, int level) const {
    double evasion = this == &RANGER ? 0.15 : 0;
    int barrier = this == &MAGE ? 30 : 0;
    if (this == &WARRIOR && level >= 3)
        barrier = 20;
    else if (this == &RANGER && level >= 5)
        barrier = 15;
    else if (this == &MAGE && level >= 3)
        evasion = 0.10;
    auto armorHandler = std::make_unique<ArmorHandler>(armor.getDefense());
    if (barrier > 0)
        armorHandler->setNext(std::make_unique<BarrierHandler>(barrier));
    if (evasion > 0) {
        auto first = std::make_unique<EvasionHandler>(evasion);
        first->setNext(std::move(armorHandler));
        return first;
    }
    return armorHandler;
}
} // namespace lab3