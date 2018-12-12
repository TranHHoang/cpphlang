#pragma once
#include "hlang/ast/ast_node.h"
#include <vector>

namespace HLang
{
    class Expression : public AstNode {
    public:
        enum class ExpressionType {
            Literal, Identifier,
            TernaryOperator, BinaryOperator, UnaryOperator,
            Assignment,
            Array,
            Call,
            Range,
        };

        Expression(ExpressionType expressionType, Token token)
                : AstNode(NodeType::Expression, std::move(token)),
                exprType(expressionType) { }
        ExpressionType getType() const { return exprType; }
    private:
        ExpressionType exprType;
    };

    using PExprNode = std::unique_ptr<HLang::Expression>;
}