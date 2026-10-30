#include "hero/hero_class.hpp"

#include <utility>

#include "core/unknown_code_error.hpp"
#include "kit/mage_kit_factory.hpp"
#include "kit/ranger_kit_factory.hpp"
#include "kit/warrior_kit_factory.hpp"

namespace lab3 {

    // лямбда без захвата превращается в обычный указатель на функцию
    const HeroClass HeroClass::WARRIOR("warrior", "Воин", 120, [](const ItemCatalog& catalog) {
        return std::unique_ptr<StarterKitFactory>(std::make_unique<WarriorKitFactory>(catalog));
    });

    const HeroClass HeroClass::RANGER("ranger", "Следопыт", 100, [](const ItemCatalog& catalog) {
        return std::unique_ptr<StarterKitFactory>(std::make_unique<RangerKitFactory>(catalog));
    });

    const HeroClass HeroClass::MAGE("mage", "Маг", 85, [](const ItemCatalog& catalog) {
        return std::unique_ptr<StarterKitFactory>(std::make_unique<MageKitFactory>(catalog));
    });

    HeroClass::HeroClass(std::string code, std::string displayName, int baseHealth, StarterKitCreator starterKit)
        : code_(std::move(code)), displayName_(std::move(displayName)), baseHealth_(baseHealth), starterKit_(starterKit) {}

    const std::vector<const HeroClass*>& HeroClass::values() {
        static const std::vector<const HeroClass*> all{&WARRIOR, &RANGER, &MAGE};
        return all;
    }

    const HeroClass& HeroClass::byCode(const std::string& code) {
        for (const HeroClass* heroClass : values()) {
            if (heroClass->code_ == code) {
                return *heroClass;
            }
        }

        throw UnknownCodeError("Класс героя", code);
    }

    std::unique_ptr<StarterKitFactory> HeroClass::getStarterKit(const ItemCatalog& catalog) const {
        return starterKit_(catalog);
    }

    const std::string& HeroClass::getCode() const {
        return code_;
    }

    const std::string& HeroClass::getDisplayName() const {
        return displayName_;
    }

    int HeroClass::getBaseHealth() const {
        return baseHealth_;
    }

}  // namespace lab3