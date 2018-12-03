#pragma once

#include "expression.h"

namespace HLang
{
    class IdentifierNode : public Expression {
    public:
        IdentifierNode(Token token)
                : Expression(ExpressionType::Identifier, std::move(token)) { }
        void accept(AstVisitor& visitor) override;
    };
}