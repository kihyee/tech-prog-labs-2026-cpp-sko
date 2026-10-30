#pragma once

#include <string>

#include "combat/hit.hpp"

namespace lab3 {

    // всё, что может участвовать в бою: и герой, и враги
    class Combatant {
    public:
        virtual ~Combatant() = default;

        // код вида сущности: класс героя или тип врага
        virtual const std::string& getCode() const = 0;

        virtual const std::string& getName() const = 0;

        virtual int getHealth() const = 0;

        virtual int getMaxHealth() const = 0;

        virtual bool isAlive() const = 0;

        // удар, который будет нанесен данной сущностью
        virtual Hit rollDamage() = 0;

        // получение удара, возвращает урон, который прошел на самом деле
        virtual int receiveHit(int damage) = 0;
    };

}  // namespace lab3