#pragma once

#include "expression.h"

namespace HLang
{
    class IdentifierExpr : public Expression {
    public:
        IdentifierExpr(Token token)
                : Expression(ExpressionType::Identifier, std::move(token)) { }
        void accept(AbstractVisitor& visitor) override;
    };
}