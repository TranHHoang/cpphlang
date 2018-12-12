#pragma once
#include "statement.h"

namespace HLang
{
    class ForStmt : public Statement {
    public:
        ForStmt(Token token, PExprNode forVar, PExprNode range, PStmtNode forBlock)
                : Statement(StatementType::If, std::move(token)),
                  forVar(std::move(forVar)),
                  forRange(std::move(range)),
                  forBlock(std::move(forBlock)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getForVar() const { return forVar.get(); }
        Expression* getRange() const { return forRange.get(); }
        Statement* getForBlock() const { return forBlock.get(); }
    private:
        PExprNode forVar;
        PExprNode forRange;
        PStmtNode forBlock;
    };

}
