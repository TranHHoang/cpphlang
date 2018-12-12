#pragma once
#include "expression.h"

namespace HLang
{
    class RangeExpr : public Expression {
    public:
        RangeExpr(Token token, PExprNode startRange, PExprNode endRange)
                : Expression(ExpressionType::Range, std::move(token)),
                  startRange(std::move(startRange)),
                  endRange(std::move(endRange)) { }

        Expression* getStartRange() const { return startRange.get(); }
        Expression* getEndRange() const { return endRange.get(); }

        void accept(AbstractVisitor &visitor) override;

    private:
        PExprNode startRange;
        PExprNode endRange;
    };
}