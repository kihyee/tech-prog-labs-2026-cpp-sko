#include "core/dice.hpp"

#include <stdexcept>

namespace lab3 {

    Dice &Dice::getInstance() {
        // единственный экземпляр - статическая переменная функции:
        // она создается при первом вызове метода и живет до конца программы
        static Dice instance;
        return instance;
    }

    Dice::Dice() : random_(std::random_device{}()) {}

    void Dice::reseed(std::uint32_t seed) {
        random_.seed(seed);
    }

    std::uint32_t Dice::nextSeed() {
        return static_cast<std::uint32_t>(roll(0, 999999));
    }

    int Dice::roll(int min, int max) {
        if (min > max) {
            throw std::invalid_argument("min must not exceed max");
        }
        const auto range = static_cast<std::uint64_t>(static_cast<std::int64_t>(max) - min) + 1;
        const std::uint64_t values = std::uint64_t{1} << 32;
        const auto limit = values - values % range;
        std::uint64_t value;
        do {
            value = random_();
        } while (value >= limit);
        return static_cast<int>(static_cast<std::int64_t>(min) + static_cast<std::int64_t>(value % range));
    }

    bool Dice::chance(double probability) {
        return static_cast<double>(random_()) / 4294967296.0 < probability;
    }

} // namespace lab3