#include "hlang/visitor/ast_visitor.h"
#include "cpp_emitter.h"
#include <hlang/visitor/analyzer/analyzer.h>
#include <map>

namespace HLang
{
    class CppGenerator : public AbstractVisitor {
    public:
        CppGenerator(std::ostream& stream, const StaticAnalyzer& analyzer)
            : emitter(stream), analyzer(analyzer) { }
        void visit(const ProgramRoot &root) override;

    private:
        void visit(const LiteralExpr &node) override;
        void visit(const CallExpr &expr) override;
        void visit(const IdentifierExpr &node) override;
        void visit(const UnaryOperatorExpr &node) override;
        void visit(const BinaryOperatorExpr &node) override;
        void visit(const TernaryOperatorExpr &node) override;
        void visit(const AssignmentExpr &node) override;
        void visit(const ArrayDeclExpr &node) override;
        void visit(const RangeExpr &expr) override;

        void visit(const AssignmentStmt &statement) override;
        void visit(const Statements &statement) override;
        void visit(const BlockStmt &stmt) override;
        void visit(const VarDeclStmt &stmt) override;
        void visit(const ParallelAssignmentStmt &stmt) override;
        void visit(const ParamDeclStmt &stmt) override;
        void visit(const ProcDeclStmt &stmt) override;

        void visit(const IfStmt &stmt) override;
        void visit(const CallStmt &stmt) override;
        void visit(const ForStmt &stmt) override;

    private:
        CppEmitter emitter;
        const StaticAnalyzer& analyzer;
    };
}