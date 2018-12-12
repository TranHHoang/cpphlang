#include "hlang/parser/expr/expr_headers.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/error/parse_error.h"

namespace HLang
{
    PExprNode ExprParser::parse(int precedence) {
        Token token = tokenStream.getNext();
        if (prefixParseMap.find(token.Type) == prefixParseMap.end()) {
            throw ParseError("Expected expression, but '" + token.Value + "' found", token);
        }
        auto expr = prefixParseMap[token.Type]->parse(*this, token);

        while (precedence < getPrecedence()) {
            token = tokenStream.getNext();
            expr = infixParseMap[token.Type]->parse(*this, std::move(expr), token);
        }

        return expr;
    }

    int ExprParser::getPrecedence() {
        return infixParseMap.find(tokenStream.peek().Type) != infixParseMap.end()
            ? infixParseMap[tokenStream.peek().Type]->getPrecedence() : 0;
    }

    void ExprParser::consume(TokenType expectedType) {
        auto token = tokenStream.getNext();
        if (token.Type != expectedType)  {
            throw ParseError(
                    token.FilePath,
                    "Expected '" + TokenToString[(int)expectedType]
                    + "', but '" + TokenToString[(int)token.Type] + "' found",
                    token.Line, token.Column);
        }
    }

    void ExprParser::registerParser() {
        registerLiteral(TokenType::IntLiteral);
        registerLiteral(TokenType::DoubleLiteral);
        registerLiteral(TokenType::BinLiteral);
        registerLiteral(TokenType::OctLiteral);
        registerLiteral(TokenType::HexLiteral);
        registerLiteral(TokenType::StringLiteral); // string

        registerPrefix(TokenType::Identifier, std::make_unique<IdentifierParse>());

        registerUnary(TokenType::Plus, Precedence::Unary);
        registerUnary(TokenType::Minus, Precedence::Unary);

        // Binary operator
        registerBinary(TokenType::Plus, Precedence::Additive);
        registerBinary(TokenType::Minus, Precedence::Additive);
        registerBinary(TokenType::Star, Precedence::Multiplicative);
        registerBinary(TokenType::Slash, Precedence::Multiplicative);
        registerBinary(TokenType::Div, Precedence::Multiplicative);
        registerBinary(TokenType::Percent, Precedence::Multiplicative);
        registerBinary(TokenType::Mod, Precedence::Multiplicative);
        registerBinaryRightAssociative(TokenType::DoubleStar, Precedence::Exponent);

        registerInfix(TokenType::Quest, std::make_unique<TernaryOperatorParse>());

        // Bitwise
        registerBinary(TokenType::BitwiseAnd, Precedence::BitwiseAnd);
        registerBinary(TokenType::BitwiseOr, Precedence::BitwiseOr);
        registerBinary(TokenType::BitwiseXor, Precedence::BitwiseXor);
        registerUnary(TokenType::BitwiseNot, Precedence::BitwiseNot);
        registerBinary(TokenType::LeftShift, Precedence::BitwiseShift);
        registerBinary(TokenType::RightShift, Precedence::BitwiseShift);

        // Comparison
        registerBinary(TokenType::Equal, Precedence::Equality);
        registerBinary(TokenType::NotEqual, Precedence::Equality);

        registerBinary(TokenType::Less, Precedence::Relational);
        registerBinary(TokenType::LessOrEqual, Precedence::Relational);
        registerBinary(TokenType::Greater, Precedence::Relational);
        registerBinary(TokenType::GreaterOrEqual, Precedence::Relational);

        // Logical
        registerBinary(TokenType::And, Precedence::LogicalAnd);
        registerBinary(TokenType::Or, Precedence::LogicalOr);
        registerUnary(TokenType::Not, Precedence::LogicalNot); // Ex: !(a == b)

        // Group
        registerPrefix(TokenType::LeftParen, std::make_unique<ParenthesesParse>()); // Ex: -2, -3

        // Assignment
        registerInfix(TokenType::Assign, std::make_unique<AssignmentParse>());

        // Call
        registerInfix(TokenType::LeftParen, std::make_unique<CallParse>());
    }

    void ExprParser::registerInfix(TokenType type, PInfix infix) {
        infixParseMap[type] = std::move(infix);
    }

    void ExprParser::registerPrefix(TokenType type, PPrefix prefix) {
        prefixParseMap[type] = std::move(prefix);
    }

    void ExprParser::registerLiteral(TokenType type) {
        registerPrefix(type, std::make_unique<LiteralParse>());
    }

    void ExprParser::registerUnary(TokenType type, Precedence precedence) {
        registerPrefix(type, std::make_unique<UnaryOperatorParse>(precedence));
    }

    void ExprParser::registerBinary(TokenType type, Precedence precedence) {
        registerInfix(type, std::make_unique<BinaryOperatorParse>(precedence, false));
    }

    void ExprParser::registerBinaryRightAssociative(TokenType type, Precedence precedence) {
        registerInfix(type, std::make_unique<BinaryOperatorParse>(precedence, true));
    }
}