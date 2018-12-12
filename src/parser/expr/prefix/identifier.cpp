#include "hlang/parser/expr/prefix/identifier.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode IdentifierParse::parse(ExprParser &parser, Token token) {
        return std::make_unique<IdentifierExpr>(std::move(token));
    }
}