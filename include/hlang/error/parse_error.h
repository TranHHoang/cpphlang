#pragma once

#include <string>
#include <exception>
#include <sstream>

namespace HLang
{
    class ParseError : public std::exception {
    public:
        ParseError() = default;
        ParseError(const std::string& file, const std::string& mes, size_t line, size_t column) {
            std::ostringstream buf;
            buf << "(" << file << ")" << "[ParseError] At (" << line << ", " << column << "): " << mes;
            message = buf.str();
        }

        ParseError(const std::string& mes, const Token& token) {
            std::ostringstream buf;
            buf << "(" << token.FilePath << ")" << "[TypeError] At (" << token.Line << ", " << token.Column << "): " << mes;
            message = buf.str();
        }

        const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}
