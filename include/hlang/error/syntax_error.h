#pragma once

#include <string>
#include <exception>
#include <sstream>

namespace HLang
{
    class SyntaxError : public std::exception {
    public:
        SyntaxError() = default;
        SyntaxError(const std::string& mes, size_t line, size_t column) {
            std::ostringstream buf;
            buf << "[SyntaxError] At (" << line << ", " << column << "): " << mes;
            message = buf.str();
        }

        const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}
