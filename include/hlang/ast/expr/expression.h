#pragma once
#include "hlang/ast/ast_node.h"
#include <vector>

namespace HLang
{
    class Expression : protected AstNode {
    protected:
        enum class ExpressionType {
            Literal, Identifier,
            TernaryOperator, BinaryOperator, UnaryOperator,
            Assignment,
            Array,
        };
    public:
        Expression(ExpressionType expressionType, Token token)
                : AstNode(NodeType::Expression, std::move(token)) { }
    };

    using PExprNode = std::unique_ptr<HLang::Expression>;
}