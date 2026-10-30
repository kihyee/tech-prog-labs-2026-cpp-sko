#include "world/location_registry.hpp"

#include <utility>

#include "core/unknown_code_error.hpp"

namespace lab3 {

    LocationRegistry::LocationRegistry(std::vector<std::unique_ptr<Location>> locations)
        : locations_(std::move(locations)) {}

    const Location& LocationRegistry::get(const std::string& code) const {
        for (const auto& location : locations_) {
            if (location->getCode() == code) {
                return *location;
            }
        }

        throw UnknownCodeError("Локация", code);
    }

    std::vector<const Location*> LocationRegistry::getAll() const {
        std::vector<const Location*> all;
        for (const auto& location : locations_) {
            all.push_back(location.get());
        }

        return all;
    }

}  // namespace lab3