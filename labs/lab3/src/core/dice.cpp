#include "core/dice.hpp"

namespace lab3 {

    Dice& Dice::getInstance() {
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
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(random_);
    }

    bool Dice::chance(double probability) {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(random_) < probability;
    }

}  // namespace lab3