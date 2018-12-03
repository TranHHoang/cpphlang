#pragma once
#include "expression.h"

namespace HLang
{
    class BinaryOperatorNode : public Expression {
    public:
        BinaryOperatorNode(Token token, PExprNode lhs, PExprNode rhs)
                : Expression(ExpressionType::BinaryOperator, std::move(token)),
                  left(std::move(lhs)), right(std::move(rhs)) { }

        void accept(AstVisitor &visitor) override;
        const Expression* getLeftExpr() const { return left.get(); }
        const Expression* getRightExpr() const { return right.get(); }
    private:
        PExprNode left, right;
    };
}