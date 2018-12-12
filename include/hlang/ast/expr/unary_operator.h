#pragma once

#include "expression.h"

namespace HLang
{
    class UnaryOperatorExpr : public Expression {
    public:
        UnaryOperatorExpr(Token token, PExprNode expr)
                : Expression(ExpressionType::UnaryOperator, std::move(token)),
                  expr(std::move(expr)) { }

        void accept(AbstractVisitor &visitor) override;
        Expression* getExpr() const { return expr.get(); }

    private:
        PExprNode expr;
    };
}