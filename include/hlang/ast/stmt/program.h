#pragma once
#include "statement.h"

namespace HLang
{
    class ProgramRoot : public Statement {
    public:
        ProgramRoot(Token token, std::vector<PStmtNode> stmtList)
                : Statement(StatementType::Program, std::move(token)),
                  stmtList(std::move(stmtList)){ }

        void accept(AbstractVisitor &visitor) override;

        const std::vector<PStmtNode>& getProgramBody() const { return stmtList; }
    private:
        std::vector<PStmtNode> stmtList;
    };
}
