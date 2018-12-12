#pragma once
#include "statement.h"

namespace HLang
{
    class BlockStmt : public Statement {
    public:
        BlockStmt(Token token, PStmtNode stmts)
                : Statement(StatementType::Block, std::move(token)),
                  stmts(std::move(stmts)){ }

        void accept(AbstractVisitor &visitor) override;

        Statement * getStmts() const { return stmts.get(); }
    private:
        PStmtNode stmts;
    };
}
