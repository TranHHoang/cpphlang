#pragma once

#include "prefix.h"
#include "hlang/parser/expr/precedence.h"

namespace HLang
{
    class UnaryOperatorParse : public IPrefix {
    public:
        UnaryOperatorParse(Precedence precedence) : precedence(precedence) { }
        PExprNode parse(ExprParser& parser, Token token) override;
    private:
        Precedence precedence;
    };
}
