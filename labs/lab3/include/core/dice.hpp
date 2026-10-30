#pragma once

#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

namespace lab3 {

    // Одиночка: общий источник случайности на всю игру
    class Dice {
    public:
        // метод для получения одиночки
        static Dice& getInstance();

        // копировать одиночку нельзя, иначе появился бы второй экземпляр
        Dice(const Dice&) = delete;
        Dice& operator=(const Dice&) = delete;

        // после установки сида все последующие броски повторяются в точности
        void reseed(std::uint32_t seed);

        // случайный сид
        std::uint32_t nextSeed();

        // случайное целое число от min до max включительно
        int roll(int min, int max);

        // возвращает true с вероятностью probability (от 0 до 1)
        bool chance(double probability);

        // случайный элемент списка
        template <typename T>
        const T& pick(const std::vector<T>& options) {
            int index = roll(0, static_cast<int>(options.size()) - 1);
            return options[static_cast<std::size_t>(index)];
        }

    private:
        // конструктор приватный - самостоятельно создать экземпляр класса нельзя
        Dice();

        std::mt19937 random_;
    };

}  // namespace lab3