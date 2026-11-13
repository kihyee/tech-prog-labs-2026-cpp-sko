#pragma once
#include "storage/hero_repository.hpp"

namespace lab3 {
    class CachingHeroRepository : public HeroRepository {
        std::unique_ptr<HeroRepository> target_;
        std::vector<std::shared_ptr<Hero>> cache_;
        bool loaded_ = false;
        void load() {
            if (!loaded_) {
                cache_ = target_->findAll();
                loaded_ = true;
            }
        }

    public:
        explicit CachingHeroRepository(std::unique_ptr<HeroRepository> target) : target_(std::move(target)) {}
        std::vector<std::shared_ptr<Hero>> findAll() override {
            load();
            return cache_;
        }
        std::shared_ptr<Hero> findByName(const std::string &name) override {
            load();
            for (auto &h : cache_)
                if (h->getName() == name)
                    return h;
            return nullptr;
        }
        void save(const std::shared_ptr<Hero> &hero) override {
            target_->save(hero);
            load();
            for (auto &h : cache_)
                if (h->getName() == hero->getName()) {
                    h = hero;
                    return;
                }
            cache_.push_back(hero);
        }
    };
} // namespace lab3