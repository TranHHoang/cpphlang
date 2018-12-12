#pragma once

#include "expression.h"

namespace HLang
{
    class AssignmentExpr : public Expression {
    public:
        AssignmentExpr(Token token, PExprNode lhs, PExprNode rhs)
                : Expression(ExpressionType::Assignment, std::move(token)),
                  lvalue(std::move(lhs)), rvalue(std::move(rhs)) { }

        void accept(AbstractVisitor &visitor) override;
        Expression* getLValue() const { return lvalue.get(); }
        Expression* getRValue() const { return rvalue.get(); }
    private:
        PExprNode lvalue, rvalue;
    };
}