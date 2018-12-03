#pragma once

#include "hlang/ast/ast_headers.h"

namespace HLang
{
    class AstVisitor {
    public:
        // expression
        virtual void visit(LiteralNode&) = 0;
        virtual void visit(IdentifierNode&) = 0;
        virtual void visit(TernaryOperatorNode&) = 0;
        virtual void visit(BinaryOperatorNode&) = 0;
        virtual void visit(UnaryOperatorNode&) = 0;
        virtual void visit(AssignmentNode&) = 0;
        virtual void visit(ArrayDeclNode&) = 0;
        // statement
        virtual void visit(ExpressionStatement&) = 0;
        virtual void visit(CompoundStatement&) = 0;
        virtual void visit(VarDeclStatement&) = 0;
    };
};