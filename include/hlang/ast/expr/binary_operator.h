#pragma once
#include "expression.h"

namespace HLang
{
    class BinaryOperatorExpr : public Expression {
    public:
        BinaryOperatorExpr(Token token, PExprNode lhs, PExprNode rhs)
                : Expression(ExpressionType::BinaryOperator, std::move(token)),
                  left(std::move(lhs)), right(std::move(rhs)) { }

        void accept(AbstractVisitor &visitor) override;
        Expression* getLeftExpr() const { return left.get(); }
        Expression* getRightExpr() const { return right.get(); }
    private:
        PExprNode left, right;
    };
}