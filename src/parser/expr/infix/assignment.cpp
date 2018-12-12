#include "hlang/ast/ast_headers.h"
#include "hlang/parser/expr/infix/assignment.h"
#include "hlang/ast/expr/expression.h"
#include "hlang/parser/expr_parser.h"

namespace HLang
{
    PExprNode AssignmentParse::parse(ExprParser &parser, PExprNode leftExpr, Token token) {
        return std::make_unique<AssignmentExpr>(token, std::move(leftExpr), parser.parse(getPrecedence() - 1));
    }
}