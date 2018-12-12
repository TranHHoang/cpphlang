#include "hlang/parser/expr/prefix/parentheses.h"
#include "hlang/parser/expr_parser.h"

namespace HLang
{
    PExprNode ParenthesesParse::parse(ExprParser &parser, Token token) {
        auto expr = parser.parse(0);
        parser.consume(TokenType::RightParen);
        return expr;
    }
}