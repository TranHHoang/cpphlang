#include "hlang/parser/expr/infix/binary_operator.h"
#include "hlang/parser/parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode BinaryOperatorParse::parse(ExprParser &parser, PExprNode leftExpr, HLang::Token token) {
        return make_unique<BinaryOperatorNode>(
                std::move(token),
                std::move(leftExpr),
                parser.parse(getPrecedence() - rightAssociative));
    }
}