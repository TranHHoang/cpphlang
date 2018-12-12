#pragma once
#include "statement.h"

namespace HLang
{
    class AssignmentStmt : public Statement {
    public:
        AssignmentStmt(Token token, PExprNode assignmentExpr)
                : Statement(StatementType::Assignment, std::move(token)),
                  assignmentExpr(std::move(assignmentExpr)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getAssignmentExpr() const { return assignmentExpr.get(); }
    private:
        PExprNode assignmentExpr;
    };

    class ParallelAssignmentStmt : public Statement {
    public:
        ParallelAssignmentStmt(Token token, vector<PExprNode> lhsList, vector<PExprNode> rhsList)
                : Statement(StatementType::ParallelAssignment, std::move(token)),
                  lhsList(std::move(lhsList)), rhsList(std::move(rhsList)) { }

        void accept(AbstractVisitor &visitor) override;

        const vector<PExprNode>& getLhsList() const { return lhsList; }
        const vector<PExprNode>& getRhsList() const { return rhsList; }
    private:
        vector<PExprNode> lhsList;
        vector<PExprNode> rhsList;
    };
}
