#pragma once

#include <string>
#include <istream>
#include <unordered_map>
#include "../utils/file_stream.h"
#include "../token/token_stream.h"
using std::string;

namespace HLang
{
    namespace
    {
        const std::unordered_map<string, TokenType> KeywordMap = {
                {"div", TokenType::Div},
                {"mod", TokenType::Mod}
        };

        const std::unordered_map<string, TokenType> OperatorMap = {
                { "+", TokenType::Plus },
                { "-", TokenType::Minus },
                { "*", TokenType::Star },
                { "**", TokenType::DoubleStar },
                { "/", TokenType::Slash },
                { "%", TokenType::Percent },
                { "=", TokenType::Assign },

                { "<", TokenType::Less },
                { "<=", TokenType::LessOrEqual },
                { ">", TokenType::Greater },
                { ">=", TokenType::GreaterOrEqual },
                { "==", TokenType::Equal },
                { "!=", TokenType::NotEqual },

                { "&&", TokenType::And },
                { "||", TokenType::Or },
                { "!", TokenType::Not },

                { "?", TokenType::Quest },
                { ":", TokenType::Colon },

                { "(", TokenType::LeftParen },
                { ")", TokenType::RightParen },

                { "&", TokenType::BitwiseAnd },
                { "|", TokenType::BitwiseOr },
                { "^", TokenType::BitwiseXor },
                { "~", TokenType::BitwiseNot },

                { "<<", TokenType::LeftShift },
                { ">>", TokenType::RightShift },

                { "[", TokenType::LeftSquareBracket },
                { "]", TokenType::RightSquareBracket },

                { ",", TokenType::Comma },
                { ";", TokenType::SemiColon }
        };
        const char * IntegerRegexPattern = "^[0-9]+(_[0-9]+)*$";
        const char * FloatRegexPattern = "^([0-9](_[0-9]+)*)*(\\.[0-9]+(_[0-9]+)*)?([eE][-+]?([0-9]+(_[0-9]+)*)+)?$";
        const size_t BasePrefixLength = 2;
    }

    class Lexer {
    public:
        Lexer(const ReadonlyFileStream& stream) : fileReader(stream) { }

        void start();
        TokenStream getTokenStream() { return tokenStream; }
    private:
        ReadonlyFileStream fileReader;
        TokenStream tokenStream;
        size_t line{0};
        size_t column{0};
    private:
        char nextChar();
        void unread();

        Token parseIdentifier();
        Token parseNumber();
        Token parseReal(const std::string& parsedValue);
        Token parseNumberWithBase(char prefix);
        Token parseString();
    };
}
