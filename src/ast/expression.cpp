#include "hlang/ast/ast_headers.h"
#include "hlang/visitor/ast_visitor.h"

namespace HLang
{
    void LiteralExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void IdentifierExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void UnaryOperatorExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void TernaryOperatorExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void BinaryOperatorExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void AssignmentExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ArrayDeclExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void CallExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void RangeExpr::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }
}