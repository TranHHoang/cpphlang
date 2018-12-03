#pragma once

#include <string>
#include <unordered_map>

namespace HLang
{
    enum class TokenType
    {
        // Special token, mark the end of token stream
        EndOfStream,

        // Integer
        IntLiteral, HexLiteral, OctLiteral, BinLiteral,

        // Double type
        DoubleLiteral,
        BoolLiteral,
        DoubleQuote, SingleQuote,

        // Keyword or identifier
        Identifier,

        // Basic operators
        Plus, Minus, Star, Slash, Div, Percent, Mod, DoubleStar,

        // Comparison operators
        Equal, NotEqual, Less, LessOrEqual, Greater, GreaterOrEqual,

        // Logic operators
        And, Or, Not,

        // Group
        LeftParen, RightParen,

        // Square bracket operators
        LeftSquareBracket, RightSquareBracket,

        // Assignment operator
        Assign,

        // Ternary operators
        Quest, Colon,

        // Bitwise operators
        LeftShift, RightShift, BitwiseAnd, BitwiseOr, BitwiseXor, BitwiseNot,

        EndBlock,

        // Special punctuations
        Comma, SemiColon,

        // Language keywords
        Var,
    };

    const std::string TokenToString[] = {
        "EndOfStream",
        "IntLiteral", "HexLiteral", "OctLiteral", "BinLiteral",
        "DoubleLiteral",
        "BoolLiteral",
        "DoubleQuote", "SingleQuote",
        "Identifier",
        "Plus", "Minus", "Star", "Slash", "Div", "Percent", "Mod", "DoubleStar",
        "Equal", "NotEqual", "Less", "LessOrEqual", "Greater", "GreaterOrEqual",
        "And", "Or", "Not",
        "LeftParen", "RightParen",
        "LeftSquareBracket", "RightSquareBracket",
        "Assign",
        "Quest", "Colon",
        "LeftShift", "RightShift", "BitwiseAnd", "BitwiseOr", "BitwiseXor", "BitwiseNot",
        "EndBlock",
        "Comma", "SemiColon",
        // Language keywords
        "Var",
    };

    struct Token
    {
        TokenType Type;
        std::string Value;
        size_t Line;
        size_t Column;
    };
}