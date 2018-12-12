#include "hlang/parser/expr/infix/binary_operator.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode BinaryOperatorParse::parse(ExprParser &parser, PExprNode leftExpr, HLang::Token token) {
        return std::make_unique<BinaryOperatorExpr>(
                std::move(token),
                std::move(leftExpr),
                parser.parse(getPrecedence() - rightAssociative));
    }
}