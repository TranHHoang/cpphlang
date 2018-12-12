#pragma once
#include "expression.h"

namespace HLang
{
    class CallExpr : public Expression {
    public:
        CallExpr(Token token, PExprNode caller, std::vector<PExprNode> args)
            : Expression(ExpressionType::Call, std::move(token)),
            funcName(std::move(caller)),
            argList(std::move(args)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getFuncName() const { return funcName.get(); }
        const std::vector<PExprNode>& getArgList() const { return argList; }
    private:
        PExprNode funcName;
        std::vector<PExprNode> argList;
    };
}