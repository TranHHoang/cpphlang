#pragma once

#include "expression.h"

namespace HLang
{
    class AssignmentNode : public Expression {
    public:
        AssignmentNode(Token token, PExprNode lhs, PExprNode rhs)
                : Expression(ExpressionType::Assignment, std::move(token)),
                  lvalue(std::move(lhs)), rvalue(std::move(rhs)) { }

        void accept(AstVisitor &visitor) override;
        const Expression* getLValue() const { return lvalue.get(); }
        const Expression* getRValue() const { return rvalue.get(); }
    private:
        PExprNode lvalue, rvalue;
    };
}