#pragma once

#include <memory>
#include <string>
#include <vector>

#include "world/location.hpp"

namespace lab3 {

    // все локации игры
    class LocationRegistry {
    public:
        // реестр становится владельцем локаций
        explicit LocationRegistry(std::vector<std::unique_ptr<Location>> locations);

        const Location& get(const std::string& code) const;

        std::vector<const Location*> getAll() const;

    private:
        std::vector<std::unique_ptr<Location>> locations_;
    };

}  // namespace lab3