#pragma once

#include "hlang/ast/expr/expression.h"

namespace HLang
{
    class ExprParser;

    class IPrefix {
    public:
        virtual PExprNode parse(ExprParser& parser, Token token) = 0;
    };
}