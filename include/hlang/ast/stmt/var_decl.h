#pragma once
#include "statement.h"

namespace HLang
{
    class VarDeclStmt : public Statement {
    public:
        VarDeclStmt(Token token, PExprNode varName, PExprNode varType, PExprNode varValue)
                : Statement(StatementType::VarDecl, std::move(token)),
                  varName(std::move(varName)), varType(std::move(varType)), varValue(std::move(varValue)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getVarName() const { return varName.get(); }
        Expression* getVarType() const { return varType.get(); }
        Expression* getVarValue() const { return varValue.get(); }
    private:
        PExprNode varName, varType, varValue;
    };
}
