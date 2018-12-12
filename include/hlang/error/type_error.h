#pragma once

#include "hlang/token/token.h"
#include <string>
#include <exception>
#include <sstream>

namespace HLang
{
    class TypeError : public std::exception {
    public:
        TypeError() = default;
        TypeError(const std::string& file, const std::string& mes, size_t line, size_t column) {
            std::ostringstream buf;
            buf << "(" << file << ")" << "[Type Error] At (" << line << ", " << column << "): " << mes;
            message = buf.str();
        }

        TypeError(const std::string& mes, const Token& token) {
            std::ostringstream buf;
            buf << "(" << token.FilePath << ")" << "[Type Error] At (" << token.Line << ", " << token.Column << "): " << mes;
            message = buf.str();
        }

        const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}
