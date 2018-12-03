#include "hlang/parser/expr/prefix/unary_operator.h"
#include "hlang/parser/parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang {
    PExprNode UnaryOperatorParse::parse(ExprParser &parser, Token token) {
        return make_unique<UnaryOperatorNode>(std::move(token), parser.parse((int) precedence));
    }
}