#pragma once

#include "infix.h"
#include "hlang/parser/expr_parser.h"
#include "hlang/parser/expr/precedence.h"

namespace HLang
{
    class CallParse : public IInfix {
    public:
        PExprNode parse(ExprParser& parser, PExprNode leftExpr, Token token) override;

        int getPrecedence() override {
            return (int)Precedence::Call;
        }
    };
}
