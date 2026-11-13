#pragma once
#include <string>
#include "core/unknown_code_error.hpp"

namespace lab3 {
    struct Achievement {
        std::string code, displayName, description;
    };
    namespace achievements {
        inline const Achievement FIRST_BLOOD{"first-blood", "Первая кровь", "одержать первую победу"};
        inline const Achievement LUCKY{"lucky", "Счастливчик", "найти зачарованный лут"};
        inline const Achievement VETERAN{"veteran", "Ветеран", "достичь 5 уровня"};
        inline const Achievement DRAGON_SLAYER{"dragon-slayer", "Драконоборец", "победить дракона"};
        inline const Achievement &byCode(const std::string &code) {
            for (auto a : {&FIRST_BLOOD, &LUCKY, &VETERAN, &DRAGON_SLAYER})
                if (a->code == code)
                    return *a;
            throw UnknownCodeError("Достижение", code);
        }
    } // namespace achievements
} // namespace lab3