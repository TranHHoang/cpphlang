#pragma once

#include "expression.h"

namespace HLang
{
    class LiteralExpr : public Expression {
    public:
        LiteralExpr(Token token)
                : Expression(ExpressionType::Literal, std::move(token)) { }
        void accept(AbstractVisitor& visitor) override;
    };
}