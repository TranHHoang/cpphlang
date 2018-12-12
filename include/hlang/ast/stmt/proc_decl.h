#pragma once
#include "statement.h"

namespace HLang
{
    class ProcDeclStmt : public Statement {
    public:
        ProcDeclStmt(Token token, PExprNode procName, vector<PStmtNode> paramList, PStmtNode body)
                : Statement(StatementType::ProcDecl, std::move(token)),
                  procName(std::move(procName)), paramList(std::move(paramList)), body(std::move(body)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getProcName() const { return procName.get(); }
        const vector<PStmtNode>& getParamList() const { return paramList; }
        Statement* getBody() const { return body.get(); }
    private:
        PExprNode procName;
        vector<PStmtNode> paramList;
        PStmtNode body;
    };
}
