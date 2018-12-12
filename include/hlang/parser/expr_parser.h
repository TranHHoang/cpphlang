#pragma once

#include "hlang/token/token_stream.h"
#include "hlang/ast/expr/expression.h"
#include "hlang/parser/expr/infix/infix.h"
#include "hlang/parser/expr/prefix/prefix.h"
#include "hlang/parser/expr/precedence.h"
#include <unordered_map>

namespace HLang
{
    using PInfix = std::unique_ptr<IInfix>;
    using PPrefix = std::unique_ptr<IPrefix>;

    class ExprParser {
    public:
        ExprParser(TokenStream tokenStream) : tokenStream(std::move(tokenStream)) {
            registerParser();
        }
        PExprNode parse(int precedence);
        void consume(TokenType expectedType);
        const TokenStream& getTokenStream() const { return tokenStream; }
    private:
        int getPrecedence();
        void registerParser();
        void registerInfix(TokenType type, PInfix infix);
        void registerPrefix(TokenType type, PPrefix prefix);
        void registerLiteral(TokenType type);
        void registerUnary(TokenType type, Precedence precedence);
        void registerBinary(TokenType type, Precedence precedence);
        void registerBinaryRightAssociative(TokenType type, Precedence precedence);

        TokenStream tokenStream;
        std::unordered_map<TokenType, PInfix> infixParseMap;
        std::unordered_map<TokenType, PPrefix> prefixParseMap;
    };
}