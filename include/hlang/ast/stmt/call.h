#pragma once
#include "statement.h"

namespace HLang
{
    class CallStmt : public Statement {
    public:
        CallStmt(Token token, PExprNode callExpr)
                : Statement(StatementType::Call, std::move(token)),
                  callExpr(std::move(callExpr)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getCallExpr() const { return callExpr.get(); }
    private:
        PExprNode callExpr;
    };
}
