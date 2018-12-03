#include "hlang/parser/expr/infix/ternary_operator.h"
#include "hlang/parser/parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode TernaryOperatorParse::parse(ExprParser &parser, PExprNode leftExpr, HLang::Token token) {
        auto trueArm = parser.parse(0);
        parser.consume(TokenType::Colon);
        auto falseArm = parser.parse(0);

        return make_unique<TernaryOperatorNode>(
                std::move(token),
                std::move(leftExpr), // condition
                std::move(trueArm), // if condition is true
                std::move(falseArm)); // else
    }
}