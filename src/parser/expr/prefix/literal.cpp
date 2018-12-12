#include "hlang/parser/expr/prefix/literal.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode LiteralParse::parse(ExprParser &parser, Token token) {
        return std::make_unique<LiteralExpr>(std::move(token));
    }
}