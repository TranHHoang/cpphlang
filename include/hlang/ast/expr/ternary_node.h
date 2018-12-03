#pragma once
#include "expression.h"

namespace HLang
{
    class TernaryOperatorNode : public Expression {
    public:
        TernaryOperatorNode(Token token, PExprNode testExpr, PExprNode trueExpr, PExprNode falseExpr)
                : Expression(ExpressionType::TernaryOperator, std::move(token)),
                  testExpr(std::move(testExpr)), trueExpr(std::move(trueExpr)), falseExpr(std::move(falseExpr)) { }

        void accept(AstVisitor &visitor) override;
        const Expression* getTestExpr() const { return testExpr.get(); }
        const Expression* getTrueExpr() const { return trueExpr.get(); }
        const Expression* getFalseExpr() const { return falseExpr.get(); }

    private:
        PExprNode testExpr, trueExpr, falseExpr;
    };
}