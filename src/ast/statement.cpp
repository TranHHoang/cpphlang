#include "hlang/ast/ast_headers.h"
#include "hlang/visitor/ast_visitor.h"

namespace HLang
{
    void AssignmentStmt::accept(HLang::AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void Statements::accept(HLang::AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void VarDeclStmt::accept(HLang::AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ParallelAssignmentStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ParamDeclStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ProcDeclStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void BlockStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ProgramRoot::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void CallStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void IfStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }

    void ForStmt::accept(AbstractVisitor &visitor) {
        visitor.visit(*this);
    }
}