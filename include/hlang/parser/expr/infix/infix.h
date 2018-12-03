#pragma once
#include "hlang/ast/expr/expression.h"
#include "hlang/parser/expr/precedence.h"

namespace HLang
{
    class ExprParser;

    class IInfix {
    public:
        virtual PExprNode parse(ExprParser& parser, PExprNode leftExpr, Token token) = 0;
        virtual int getPrecedence() = 0;
    };
}
