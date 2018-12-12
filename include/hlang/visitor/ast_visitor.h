#pragma once

#include "hlang/ast/ast_headers.h"

namespace HLang
{
    class AbstractVisitor {
    public:
        // expression
        virtual void visit(const LiteralExpr&) = 0;
        virtual void visit(const CallExpr&) = 0;
        virtual void visit(const IdentifierExpr&) = 0;
        virtual void visit(const UnaryOperatorExpr&) = 0;
        virtual void visit(const BinaryOperatorExpr&) = 0;
        virtual void visit(const TernaryOperatorExpr&) = 0;
        virtual void visit(const AssignmentExpr&) = 0;
        virtual void visit(const ArrayDeclExpr&) = 0;
        virtual void visit(const RangeExpr&) = 0;
        // statement
        virtual void visit(const ProgramRoot&) = 0;
        virtual void visit(const AssignmentStmt&) = 0;
        virtual void visit(const ParallelAssignmentStmt&) = 0;
        virtual void visit(const Statements&) = 0;
        virtual void visit(const BlockStmt&) = 0;
        virtual void visit(const VarDeclStmt&) = 0;
        virtual void visit(const ParamDeclStmt&) = 0;
        virtual void visit(const ProcDeclStmt&) = 0;
        virtual void visit(const CallStmt&) = 0;
        virtual void visit(const IfStmt&) = 0;
        virtual void visit(const ForStmt&) = 0;

    };
};