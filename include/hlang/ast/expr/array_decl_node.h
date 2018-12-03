#pragma once
#include "expression.h"

namespace HLang
{
    class ArrayDeclNode : public Expression {
    public:
        ArrayDeclNode(Token token, std::vector<PExprNode> items)
                : Expression(ExpressionType::Array, std::move(token)),
                  itemList(std::move(items)) { }

        const std::vector<PExprNode>& getItemList() const { return itemList; }
        void accept(AstVisitor &visitor) override;

    private:
        std::vector<PExprNode> itemList;
    };
}