#pragma once
#include "statement.h"

namespace HLang
{
    class ParamDeclStmt : public Statement {
    public:
        ParamDeclStmt(Token token, PExprNode paramModifier, PExprNode paramName, PExprNode paramType, PExprNode paramValue)
                : Statement(StatementType::ParamDecl, std::move(token)),
                  paramModifier(std::move(paramModifier)),
                  paramName(std::move(paramName)),
                  paramType(std::move(paramType)),
                  paramValue(std::move(paramValue)) { }

        void accept(AbstractVisitor &visitor) override;

        Expression* getParamModifier() const { return paramModifier.get(); }
        Expression* getParamName() const { return paramName.get(); }
        Expression* getParamType() const { return paramType.get(); }
        Expression* getParamValue() const { return paramValue.get(); }
    private:
        PExprNode paramModifier, paramName, paramType, paramValue;
    };
}
