#pragma once

#include "expression.h"

namespace HLang
{
    class LiteralNode : public Expression {
    public:
        LiteralNode(Token token)
                : Expression(ExpressionType::Literal, std::move(token)) { }
        void accept(AstVisitor& visitor) override;
    };
}