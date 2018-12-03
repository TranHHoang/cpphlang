#pragma once

#include "expression.h"

namespace HLang
{
    class UnaryOperatorNode : public Expression {
    public:
        UnaryOperatorNode(Token token, PExprNode expr)
                : Expression(ExpressionType::UnaryOperator, std::move(token)),
                  expr(std::move(expr)) { }

        void accept(AstVisitor &visitor) override;
        const Expression* getExpr() const { return expr.get(); }

    private:
        PExprNode expr;
    };
}