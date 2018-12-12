#pragma once
#include "statement.h"

namespace HLang
{
    class Statements : public Statement {
    public:
        Statements(Token token, std::vector<PStmtNode> stmts)
                : Statement(StatementType::Statements, std::move(token)),
                  statementList(std::move(stmts)){ }

        void accept(AbstractVisitor &visitor) override;

        const vector<PStmtNode>& getStmtList() const { return statementList; }
    private:
        vector<PStmtNode> statementList;
    };
}
