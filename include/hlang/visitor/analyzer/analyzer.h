#pragma once

#include "hlang/visitor/ast_visitor.h"
#include <typeindex>
#include <map>
#include <unordered_map>

namespace HLang
{
    struct VariableSignature {
        std::string name;
        std::string type;
    };

    struct FunctionSignature {
        std::string name;
        vector<VariableSignature> paramList;
        std::string type;
    };

    class StaticAnalyzer : public AbstractVisitor {
    public:
        void visit(const ProgramRoot &root) override;

    private:
        void visit(const LiteralExpr &expr) override;

        void visit(const IdentifierExpr &expr) override;

        void visit(const TernaryOperatorExpr &expr) override;

        void visit(const BinaryOperatorExpr &expr) override;

        void visit(const UnaryOperatorExpr &expr) override;

        void visit(const AssignmentExpr &expr) override;

        void visit(const ArrayDeclExpr &expr) override;

        void visit(const RangeExpr &expr) override;

        void visit(const AssignmentStmt &stmt) override;

        void visit(const Statements &stmt) override;

        void visit(const BlockStmt &stmt) override;

        void visit(const VarDeclStmt &stmt) override;

        void visit(const ParallelAssignmentStmt &stmt) override;

        void visit(const ProcDeclStmt &stmt) override;

        void visit(const ParamDeclStmt &stmt) override;

        void visit(const CallExpr &expr) override;

        void visit(const CallStmt &stmt) override;

        void visit(const IfStmt &stmt) override;

        void visit(const ForStmt &stmt) override;

    public:
        auto getVarSymbolTable() const { return varSymbolTable; }
        auto getFuncSymbolTable() const { return funcSymbolTable; }

    private:
        std::string resultType;
        std::map<std::string, std::string> varSymbolTable;
        std::multimap<std::string, FunctionSignature> funcSymbolTable;
    };
//    enum class TypeRanking {
//        Int,
//        Double,
//    };
//
//    const std::unordered_map<std::string, TypeRanking> TypeRanking = {
//            {"int", TypeRanking::Int},
//            {"double", TypeRanking::Double}
//    };
}