#pragma once
#include "hlang/ast/ast_node.h"
#include "hlang/ast/expr/expression.h"
#include <vector>
using std::vector;

namespace HLang
{
    class Statement : public AstNode {
    public:
        enum class StatementType {
            Program,
            Assignment, ParallelAssignment,
            Statements, Block,
            Call,
            If, For, While, Case,
            VarDecl, ParamDecl,
            ProcDecl, FuncDecl
        };
    public:
        Statement(StatementType statementType, Token token)
                : AstNode(NodeType::Statement, std::move(token)),
                stmtType(statementType) { }

        StatementType getType() const { return stmtType; }
    private:
        StatementType stmtType;
    };

    using PStmtNode = std::unique_ptr<Statement>;
}