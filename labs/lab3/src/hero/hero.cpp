#include "hero/hero.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace lab3 {

namespace {

int utf8Length(const std::string& text) {
    int length = 0;
    for (unsigned char byte : text) {
        if ((byte & 0xC0) != 0x80) {
            length++;
        }
    }

    return length;
}

bool isBlank(const std::string& text) {
    return text.find_first_not_of(" \t\r\n") == std::string::npos;
}

}  // namespace

// строитель

Hero::Builder& Hero::Builder::setName(std::string name) {
    name_ = std::move(name);
    return *this;
}

Hero::Builder& Hero::Builder::setHeroClass(const HeroClass& heroClass) {
    heroClass_ = &heroClass;
    return *this;
}

Hero::Builder& Hero::Builder::setWeapon(std::shared_ptr<Weapon> weapon) {
    weapon_ = std::move(weapon);
    return *this;
}

Hero::Builder& Hero::Builder::setArmor(std::shared_ptr<Armor> armor) {
    armor_ = std::move(armor);
    return *this;
}

Hero::Builder& Hero::Builder::setStarterKit(const StarterKitFactory& starterKit) {
    weapon_ = starterKit.createWeapon();
    armor_ = starterKit.createArmor();
    return *this;
}

Hero::Builder& Hero::Builder::setLevel(int level) {
    level_ = level;
    return *this;
}

Hero::Builder& Hero::Builder::setGold(int gold) {
    gold_ = gold;
    return *this;
}

Hero Hero::Builder::build() const {
    if (isBlank(name_)) {
        throw std::invalid_argument("У героя должно быть имя");
    }
    if (utf8Length(name_) > MAX_NAME_LENGTH) {
        throw std::invalid_argument(
            "Имя героя не может быть длиннее " + std::to_string(MAX_NAME_LENGTH) + " символов"
        );
    }
    if (heroClass_ == nullptr) {
        throw std::invalid_argument("Не выбран класс героя");
    }
    if (weapon_ == nullptr || armor_ == nullptr) {
        throw std::invalid_argument("Герою нужны оружие и броня");
    }
    if (level_ < 1) {
        throw std::invalid_argument("Уровень героя не может быть меньше 1");
    }
    if (gold_ < 0) {
        throw std::invalid_argument("Золота не может быть меньше нуля");
    }

    return Hero(*this);
}

// герой

Hero::Hero(const Builder& builder)
    : name_(builder.name_),
      heroClass_(builder.heroClass_),
      level_(builder.level_),
      gold_(builder.gold_),
      health_(0),
      weapon_(builder.weapon_),
      armor_(builder.armor_) {
    health_ = getMaxHealth();
}

Hit Hero::rollDamage() {
    Hit hit = weapon_->rollDamage();
    return {hit.damage + (level_ - 1) * DAMAGE_PER_LEVEL, hit.critical};
}

int Hero::receiveHit(int damage) {
    int reducedDamage = static_cast<int>(std::lround(damage * (1 - armor_->getDefense())));
    // хотя бы единицу урона броня пропускает всегда
    int dealt = std::max(1, reducedDamage);
    health_ = std::max(0, health_ - dealt);
    return dealt;
}

bool Hero::isAlive() const {
    return health_ > 0;
}

void Hero::restoreHealth() {
    health_ = getMaxHealth();
}

int Hero::gainExperience(int amount) {
    experience_ += amount;
    int levelsGained = 0;
    while (experience_ >= getExperienceToNextLevel()) {
        experience_ -= getExperienceToNextLevel();
        level_++;
        levelsGained++;
    }

    return levelsGained;
}

void Hero::addGold(int amount) {
    gold_ += amount;
}

void Hero::spendGold(int amount) {
    if (amount > gold_) {
        throw std::runtime_error(
            "Не хватает золота: нужно " + std::to_string(amount) + ", есть " + std::to_string(gold_)
        );
    }

    gold_ -= amount;
}

void Hero::addItem(std::shared_ptr<Item> item) {
    inventory_.push_back(std::move(item));
}

void Hero::removeItem(const std::shared_ptr<Item>& item) {
    auto position = std::find(inventory_.begin(), inventory_.end(), item);
    if (position == inventory_.end()) {
        throw std::invalid_argument("В инвентаре нет предмета " + item->getName());
    }

    inventory_.erase(position);
}

void Hero::equip(const std::shared_ptr<Item>& item) {
    // dynamic_pointer_cast вернет пустой указатель, если предмет другого типа
    if (auto newWeapon = std::dynamic_pointer_cast<Weapon>(item)) {
        removeItem(item);
        inventory_.push_back(weapon_);
        weapon_ = newWeapon;
    } else if (auto newArmor = std::dynamic_pointer_cast<Armor>(item)) {
        removeItem(item);
        inventory_.push_back(armor_);
        armor_ = newArmor;
    } else {
        throw std::invalid_argument("Предмет нельзя экипировать: " + item->getName());
    }
}

const std::string& Hero::getCode() const {
    return heroClass_->getCode();
}

const std::string& Hero::getName() const {
    return name_;
}

int Hero::getHealth() const {
    return health_;
}

int Hero::getMaxHealth() const {
    return heroClass_->getBaseHealth() + (level_ - 1) * HEALTH_PER_LEVEL;
}

const HeroClass& Hero::getHeroClass() const {
    return *heroClass_;
}

int Hero::getLevel() const {
    return level_;
}

int Hero::getExperience() const {
    return experience_;
}

int Hero::getExperienceToNextLevel() const {
    return level_ * EXPERIENCE_PER_LEVEL;
}

int Hero::getGold() const {
    return gold_;
}

const Weapon& Hero::getWeapon() const {
    return *weapon_;
}

const Armor& Hero::getArmor() const {
    return *armor_;
}

const std::vector<std::shared_ptr<Item>>& Hero::getInventory() const {
    return inventory_;
}

}  // namespace lab3