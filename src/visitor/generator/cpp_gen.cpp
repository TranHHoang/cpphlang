#include "hlang/visitor/generator/cpp_gen.h"
#include <string>
#include <algorithm>
#include <sstream>

using namespace HLang;
using std::string;

// We already checked everything, so we do not check anything during codegen phrase

void CppGenerator::visit(const LiteralExpr &node) {
    // TODO: Check for integer overflow and choose BigInt type
    // Since C++ do not allow underscore separator for literal, we need to remove it before convert
    string value = node.getToken().Value;
    value.erase(std::remove(value.begin(), value.end(), '_'), value.end());

    switch (node.getToken().Type) {
        case TokenType::BinLiteral:
            emitter.emitRaw("0b" + value);
            break;
        case TokenType::OctLiteral:
            emitter.emitRaw("0" + value);
            break;
        case TokenType::IntLiteral:
        case TokenType::BoolLiteral:
            emitter.emitRaw(value);
            break;
        case TokenType::HexLiteral:
            emitter.emitRaw("0x" + value);
            break;
        case TokenType::DoubleLiteral:
            emitter.emitRaw(value);
            break;
        case TokenType::StringLiteral:
            emitter.emitRaw('"' + value + '"');
            break;
        default:
            // TODO: Something
            break;
    }
}

void CppGenerator::visit(const IdentifierExpr &node) {
    emitter.emitRaw(node.getToken().Value);
}

void CppGenerator::visit(const UnaryOperatorExpr &node) {
    emitter.emitRaw(node.getToken().Value);
    node.getExpr()->accept(*this);
}

void CppGenerator::visit(const BinaryOperatorExpr &node) {
    emitter.emitRaw("(");
    node.getLeftExpr()->accept(*this);
    emitter.emitRaw(node.getToken().Value);
    node.getRightExpr()->accept(*this);
    emitter.emitRaw(")");
}

void CppGenerator::visit(const TernaryOperatorExpr &node) {
    emitter.emitRaw("(");

    node.getTestExpr()->accept(*this);
    emitter.emitRaw("?");
    node.getTrueExpr()->accept(*this);
    emitter.emitRaw(":");
    node.getFalseExpr()->accept(*this);

    emitter.emitRaw(")");
}

void CppGenerator::visit(const AssignmentExpr &node) {
    emitter.emitRaw("(");

    node.getLValue()->accept(*this);
    emitter.emitRaw("=");
    node.getRValue()->accept(*this);

    emitter.emitRaw(")");
}

void CppGenerator::visit(const ArrayDeclExpr &node) {
    // TODO: first, declare List object
}

void CppGenerator::visit(const AssignmentStmt &statement) {
//    visit(dynamic_cast<const AssignmentExpr&>(*statement.getAssignmentExpr()));
    statement.getAssignmentExpr()->accept(*this);
    emitter.emitRaw(";");
}

void CppGenerator::visit(const Statements &statement) {
    for (auto &stmt : statement.getStmtList()) {
        stmt->accept(*this);
//        emitter.emitRaw("\n");
    }
}

void CppGenerator::visit(const ParallelAssignmentStmt &stmt) {
    emitter.includeCppStdLib("tuple");
    emitter.emitRaw("std::tie(");
    for (auto i = 0; i < stmt.getLhsList().size(); i++) {
        stmt.getLhsList()[i]->accept(*this);
        if (stmt.getLhsList()[i] != stmt.getLhsList().back()) {
            emitter.emitRaw(",");
        }
    }
    emitter.emitRaw(")=std::make_tuple(");
    for (auto i = 0; i < stmt.getRhsList().size(); i++) {
        stmt.getRhsList()[i]->accept(*this);
        if (stmt.getRhsList()[i] != stmt.getRhsList().back()) {
            emitter.emitRaw(",");
        }
    }
    emitter.emitRaw(");");
}

void CppGenerator::visit(const VarDeclStmt &stmt) {
    // var a[: int] = 10, b = 11 => var a = 10 \n var b = 11;
    if (stmt.getVarType() != nullptr) {
        stmt.getVarType()->accept(*this);
    }
    else {
        emitter.emitRaw(analyzer.getVarSymbolTable()[stmt.getVarName()->getToken().Value], Opcode::TypeDecl);
    }
    stmt.getVarName()->accept(*this);
    emitter.emitRaw("=");
    stmt.getVarValue()->accept(*this);
    emitter.emitRaw(";");
}

void CppGenerator::visit(const ParamDeclStmt &stmt) {
    stmt.getParamType()->accept(*this);
    emitter.emitRaw(" ");
    stmt.getParamName()->accept(*this);

    if (stmt.getParamValue() != nullptr) {
        emitter.emitRaw("=");
        stmt.getParamType()->accept(*this);
    }
}

void CppGenerator::visit(const ProcDeclStmt &stmt) {
    emitter.emitRaw("void", Opcode::CppKeyword);
    stmt.getProcName()->accept(*this);
    emitter.emitRaw("(");
    for (auto i = 0; i < stmt.getParamList().size(); i++) {
        stmt.getParamList()[i]->accept(*this);
        if (stmt.getParamList()[i] != stmt.getParamList().back()) {
            emitter.emitRaw(",");
        }
    }
    emitter.emitRaw(")");
    stmt.getBody()->accept(*this);
}

void CppGenerator::visit(const BlockStmt &stmt) {
    emitter.emitRaw("{\n");
    stmt.getStmts()->accept(*this);
    emitter.emitRaw("\n}\n");
}

void CppGenerator::visit(const ProgramRoot &root) {
    for (auto &stmt : root.getProgramBody()) {
        stmt->accept(*this);
    }
}

void CppGenerator::visit(const IfStmt &stmt) {
    emitter.emitRaw("if", Opcode::CppKeyword);
    emitter.emitRaw("(");
    stmt.getCondExpr()->accept(*this);
    emitter.emitRaw(")");
    stmt.getIfBlock()->accept(*this);
    if (stmt.getElseBlock() != nullptr) {
        emitter.emitRaw("else", Opcode::CppKeyword);
        stmt.getElseBlock()->accept(*this);
    }
}

void CppGenerator::visit(const CallExpr &expr) {

}

void CppGenerator::visit(const CallStmt &stmt) {

}

void CppGenerator::visit(const ForStmt &stmt) {

}

void CppGenerator::visit(const RangeExpr &expr) {

}
