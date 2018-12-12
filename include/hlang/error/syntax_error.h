#pragma once

#include <string>
#include <exception>
#include <sstream>

namespace HLang
{
    class SyntaxError : public std::exception {
    public:
        SyntaxError() = default;
        SyntaxError(const std::string& file, const std::string& mes, size_t line, size_t column) {
            std::ostringstream buf;
            buf << "(" << file << ")" << "[Syntax Error] At (" << line << ", " << column << "): " << mes;
            message = buf.str();
        }

        SyntaxError(const std::string& mes, const Token& token) {
            std::ostringstream buf;
            buf << "(" << token.FilePath << ")" << "[Syntax Error] At (" << token.Line << ", " << token.Column << "): " << mes;
            message = buf.str();
        }

        const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}
