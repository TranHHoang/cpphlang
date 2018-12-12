#pragma once
#include "expression.h"

namespace HLang
{
    class TernaryOperatorExpr : public Expression {
    public:
        TernaryOperatorExpr(Token token, PExprNode testExpr, PExprNode trueExpr, PExprNode falseExpr)
                : Expression(ExpressionType::TernaryOperator, std::move(token)),
                  testExpr(std::move(testExpr)), trueExpr(std::move(trueExpr)), falseExpr(std::move(falseExpr)) { }

        void accept(AbstractVisitor &visitor) override;
        Expression* getTestExpr() const { return testExpr.get(); }
        Expression* getTrueExpr() const { return trueExpr.get(); }
        Expression* getFalseExpr() const { return falseExpr.get(); }

    private:
        PExprNode testExpr, trueExpr, falseExpr;
    };
}