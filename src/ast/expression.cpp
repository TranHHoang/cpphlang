#include "hlang/ast/ast_headers.h"
#include "hlang/visitor/ast_visitor.h"

namespace HLang
{
    void LiteralNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void IdentifierNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void UnaryOperatorNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void TernaryOperatorNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void BinaryOperatorNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void AssignmentNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void ArrayDeclNode::accept(AstVisitor &visitor) {
        visitor.visit(*this);
    }
}