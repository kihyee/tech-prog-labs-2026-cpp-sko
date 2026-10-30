#include "item/default_catalog.hpp"

#include <memory>

#include "item/armor.hpp"
#include "item/bow.hpp"
#include "item/staff.hpp"
#include "item/sword.hpp"

namespace lab3 {

    ItemCatalog createDefaultCatalog() {
        ItemCatalog catalog;

        // стартовое снаряжение
        catalog.add(std::make_unique<Sword>(item_codes::TRAINING_SWORD, "Тренировочный меч", 20, 12));
        catalog.add(std::make_unique<Bow>(item_codes::HUNTING_BOW, "Охотничий лук", 20, 10, 0.3));
        catalog.add(std::make_unique<Staff>(item_codes::APPRENTICE_STAFF, "Посох ученика", 20, 14, 0.3));
        catalog.add(std::make_unique<Armor>(item_codes::CHAINMAIL, "Кольчуга", 40, 0.3));
        catalog.add(std::make_unique<Armor>(item_codes::LEATHER_ARMOR, "Кожаная броня", 30, 0.2));
        catalog.add(std::make_unique<Armor>(item_codes::LINEN_ROBE, "Льняная роба", 15, 0.1));

        // товары торговца
        catalog.add(std::make_unique<Sword>(item_codes::IRON_SWORD, "Железный меч", 80, 17));
        catalog.add(std::make_unique<Bow>(item_codes::ELVEN_BOW, "Эльфийский лук", 90, 14, 0.4));
        catalog.add(std::make_unique<Staff>(item_codes::EMBER_STAFF, "Тлеющий посох", 90, 20, 0.3));
        catalog.add(std::make_unique<Armor>(item_codes::PLATE_ARMOR, "Латы", 120, 0.4));

        // добыча
        catalog.add(std::make_unique<Sword>(item_codes::GOBLIN_CLEAVER, "Гоблинский тесак", 40, 15));
        catalog.add(std::make_unique<Bow>(item_codes::BONE_BOW, "Костяной лук", 140, 17, 0.4));
        catalog.add(std::make_unique<Staff>(item_codes::NECROMANCER_STAFF, "Посох некроманта", 150, 25, 0.35));
        catalog.add(std::make_unique<Sword>(item_codes::KNIGHT_BLADE, "Клинок рыцаря", 150, 23));
        catalog.add(std::make_unique<Armor>(item_codes::CRYPT_MAIL, "Кольчуга стража склепа", 160, 0.45));
        catalog.add(std::make_unique<Sword>(item_codes::DAWN_BLADE, "Клинок рассвета", 500, 35));
        catalog.add(std::make_unique<Armor>(item_codes::DRAGONSCALE_ARMOR, "Драконья чешуя", 500, 0.55));

        return catalog;
    }

}  // namespace lab3