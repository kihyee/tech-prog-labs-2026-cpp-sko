#pragma once

#include <stdexcept>
#include <string>

namespace lab3 {

    class UnknownCodeError : public std::runtime_error {
    public:
        UnknownCodeError(const std::string& what, const std::string& code)
            : std::runtime_error(what + " с кодом '" + code + "' не существует") {}
    };

}  // namespace lab3