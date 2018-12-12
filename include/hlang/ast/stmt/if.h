#pragma once
#include "statement.h"

namespace HLang
{
    class IfStmt : public Statement {
    public:
        IfStmt(Token token, PExprNode ifCond, PStmtNode ifBlock, PStmtNode elseBlock)
                : Statement(StatementType::If, std::move(token)),
                  condExpr(std::move(ifCond)),
                  ifBlock(std::move(ifBlock)),
                  elseBlock(std::move(elseBlock)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getCondExpr() const { return condExpr.get(); }
        Statement* getIfBlock() const { return ifBlock.get(); }
        Statement* getElseBlock() const { return elseBlock.get(); }
    private:
        PExprNode condExpr;
        PStmtNode ifBlock;
        PStmtNode elseBlock;
    };
}
