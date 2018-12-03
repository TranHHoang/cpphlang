#include "hlang/parser/expr/prefix/identifier.h"
#include "hlang/parser/parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang
{
    PExprNode IdentifierParse::parse(ExprParser &parser, Token token) {
        return make_unique<IdentifierNode>(std::move(token));
    }
}