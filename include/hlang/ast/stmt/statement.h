#pragma once
#include "hlang/ast/ast_node.h"
#include "hlang/ast/expr/expression.h"
#include <vector>

namespace HLang
{
    class Statement : protected AstNode {
    protected:
        enum class StatementType {
            Expression, Compound,
            VarDecl, ProcDecl, FuncDecl
        };
    public:
        Statement(StatementType statementType, Token token)
                : AstNode(NodeType::Statement, std::move(token)) { }
    };

    using PStmtNode = std::unique_ptr<HLang::Statement>;

    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement(Token token, PExprNode expr)
        : Statement(StatementType::Expression, std::move(token)),
        expr(std::move(expr)) { }

        void accept(AstVisitor &visitor) override;

        const Expression* getExpr() const { return expr.get(); }
    private:
        PExprNode expr;
    };

    class CompoundStatement : public Statement {
    public:
        CompoundStatement(Token token, std::vector<PStmtNode> stmts)
            : Statement(StatementType::Compound, std::move(token)),
            statementList(std::move(stmts)){ }

        void accept(AstVisitor &visitor) override;

        const std::vector<PStmtNode>& getStmtList() const { return statementList; }
    private:
        std::vector<PStmtNode> statementList;
    };

    class VarDeclStatement : public Statement {
    public:
        VarDeclStatement(Token token, PExprNode varName, PExprNode varType, PExprNode varValue)
            : Statement(StatementType::VarDecl, std::move(token)),
              varName(std::move(varName)), varType(std::move(varType)), varValue(std::move(varValue)) { }

        void accept(AstVisitor &visitor) override;

        const Expression* getVarName() const { return varName.get(); }
        const Expression* getVarType() const { return varType.get(); }
        const Expression* getVarValue() const { return varValue.get(); }
    private:
        PExprNode varName, varType, varValue;
    };
}