#include "hlang/ast/stmt/statement.h"
#include "hlang/visitor/ast_visitor.h"

namespace HLang
{
    void ExpressionStatement::accept(HLang::AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void CompoundStatement::accept(HLang::AstVisitor &visitor) {
        visitor.visit(*this);
    }

    void VarDeclStatement::accept(HLang::AstVisitor &visitor) {
        visitor.visit(*this);
    }
}