#pragma once
#include <memory>
#include <vector>
#include "hero/hero.hpp"

namespace lab3 {
    class HeroRepository {
    public:
        virtual ~HeroRepository() = default;
        virtual std::shared_ptr<Hero> findByName(const std::string &name) = 0;
        virtual std::vector<std::shared_ptr<Hero>> findAll() = 0;
        virtual void save(const std::shared_ptr<Hero> &hero) = 0;
    };
} // namespace lab3