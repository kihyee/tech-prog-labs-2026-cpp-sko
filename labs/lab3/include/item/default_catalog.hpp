#pragma once

#include "item/item_catalog.hpp"

namespace lab3 {

    namespace item_codes {

        // коды шаблонов: по ним предметы ищутся в каталоге
        // стартовое снаряжение
        inline constexpr const char* TRAINING_SWORD = "training-sword";
        inline constexpr const char* HUNTING_BOW = "hunting-bow";
        inline constexpr const char* APPRENTICE_STAFF = "apprentice-staff";
        inline constexpr const char* CHAINMAIL = "chainmail";
        inline constexpr const char* LEATHER_ARMOR = "leather-armor";
        inline constexpr const char* LINEN_ROBE = "linen-robe";

        // товары торговца
        inline constexpr const char* IRON_SWORD = "iron-sword";
        inline constexpr const char* ELVEN_BOW = "elven-bow";
        inline constexpr const char* EMBER_STAFF = "ember-staff";
        inline constexpr const char* PLATE_ARMOR = "plate-armor";

        // добыча
        inline constexpr const char* GOBLIN_CLEAVER = "goblin-cleaver";
        inline constexpr const char* BONE_BOW = "bone-bow";
        inline constexpr const char* NECROMANCER_STAFF = "necromancer-staff";
        inline constexpr const char* KNIGHT_BLADE = "knight-blade";
        inline constexpr const char* CRYPT_MAIL = "crypt-mail";
        inline constexpr const char* DAWN_BLADE = "dawn-blade";
        inline constexpr const char* DRAGONSCALE_ARMOR = "dragonscale-armor";

    }  // namespace item_codes

    // все предметы, которые есть в игре
    ItemCatalog createDefaultCatalog();

}  // namespace lab3