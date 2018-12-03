#pragma once

#include "infix.h"
#include "hlang/parser/expr/precedence.h"

namespace HLang
{
    class BinaryOperatorParse : public IInfix {
    public:
        BinaryOperatorParse(Precedence precedence, bool rightAssociative)
            : precedence(precedence), rightAssociative(rightAssociative) {
        }

        PExprNode parse(ExprParser& parser, PExprNode leftExpr, Token token) override;

        int getPrecedence() override {
            return (int)precedence;
        }
    private:
        Precedence precedence;
        bool rightAssociative;
    };
}

