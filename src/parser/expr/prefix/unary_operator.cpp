#include "hlang/parser/expr/prefix/unary_operator.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/ast/ast_headers.h"

namespace HLang {
    PExprNode UnaryOperatorParse::parse(ExprParser &parser, Token token) {
        return std::make_unique<UnaryOperatorExpr>(std::move(token), parser.parse((int) precedence));
    }
}