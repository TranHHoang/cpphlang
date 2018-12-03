#include "hlang/parser/expr/prefix/literal.h"
#include "hlang/parser/parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode LiteralParse::parse(ExprParser &parser, Token token) {
        return make_unique<LiteralNode>(std::move(token));
    }
}