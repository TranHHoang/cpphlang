#pragma once
#include "expression.h"

namespace HLang
{
    class ArrayDeclExpr : public Expression {
    public:
        ArrayDeclExpr(Token token, std::vector<PExprNode> items)
                : Expression(ExpressionType::Array, std::move(token)),
                  itemList(std::move(items)) { }

        const std::vector<PExprNode>& getItemList() const { return itemList; }
        void accept(AbstractVisitor &visitor) override;

    private:
        std::vector<PExprNode> itemList;
    };
}