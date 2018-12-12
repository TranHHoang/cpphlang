#include "hlang/visitor/analyzer/analyzer.h"
#include "hlang/error/type_error.h"
#include <string>

using namespace HLang;
using std::string;

void StaticAnalyzer::visit(const LiteralExpr &expr) {
    switch (expr.getToken().Type) {
        case TokenType::DoubleLiteral:
            resultType = "Double";
            break;
        case TokenType::BoolLiteral:
            resultType = "Bool";
            break;
        case TokenType::StringLiteral:
            resultType = "String";
            break;
        default:
            resultType = "Int";
            break;
    }
}

void StaticAnalyzer::visit(const IdentifierExpr &expr) {
    string value = expr.getToken().Value;
    if (varSymbolTable.find(value) == varSymbolTable.end()) {
        throw TypeError("Used of undeclared symbol '" + value + "'", expr.getToken());
    }
    resultType = varSymbolTable.at(value);
}

void StaticAnalyzer::visit(const UnaryOperatorExpr &expr) {
    expr.getExpr()->accept(*this);
    auto exprType = resultType;

    if (exprType != "Int" || exprType != "Double") {
        throw TypeError("No overloading unary operator '" + expr.getToken().Value + "' of type '" + exprType + "'", expr.getToken());
    }
}

void StaticAnalyzer::visit(const BinaryOperatorExpr &expr) {
    expr.getLeftExpr()->accept(*this);
    auto lhsType = resultType;
    expr.getRightExpr()->accept(*this);
    auto rhsType = resultType;

    if (lhsType != rhsType) {
        throw TypeError("No overloading binary operator '" + expr.getToken().Value + "' between '" + lhsType + "' and '" + rhsType + "'", expr.getToken());
    }

    switch (expr.getToken().Type) {
        case TokenType::Equal:
        case TokenType::NotEqual:
        case TokenType::Less:
        case TokenType::LessOrEqual:
        case TokenType::Greater:
        case TokenType::GreaterOrEqual:
        case TokenType::And:
        case TokenType::Or:
            resultType = "Bool";
            break;
        default:
            break;
    }
//    resultType = lhsType;
}

void StaticAnalyzer::visit(const TernaryOperatorExpr &expr) {
    expr.getTestExpr()->accept(*this);
    auto exprType = resultType;
    if (exprType != "Bool") {
        throw TypeError("Unable to cast type '" + exprType + "' to 'Bool'", expr.getToken());
    }
    expr.getTrueExpr()->accept(*this);
    expr.getFalseExpr()->accept(*this);
}

void StaticAnalyzer::visit(const AssignmentExpr &expr) {
    expr.getLValue()->accept(*this);
    auto lhsType = resultType;
    expr.getRValue()->accept(*this);
    auto rhsType = resultType;

    if (lhsType != rhsType)
        throw TypeError("Incompatible type when casting type '" + rhsType + "' to type '" + lhsType + "'", expr.getToken());

}

void StaticAnalyzer::visit(const ArrayDeclExpr &expr) {

}

void StaticAnalyzer::visit(const AssignmentStmt &stmt) {
    visit(dynamic_cast<const AssignmentExpr&>(*stmt.getAssignmentExpr()));
}

void StaticAnalyzer::visit(const Statements &stmt) {
    for (auto &stmt : stmt.getStmtList()) {
        stmt->accept(*this);
    }
}

void StaticAnalyzer::visit(const VarDeclStmt &stmt) {
    string varName = dynamic_cast<IdentifierExpr&>(*stmt.getVarName()).getToken().Value;
    if (varSymbolTable.find(varName) != varSymbolTable.end())
        throw TypeError("Redeclaration of '" + varName + "'", stmt.getToken());

    // TODO: Support generic
    string varType;
    if (stmt.getVarType() != nullptr) {
        stmt.getVarType()->accept(*this);
        varType = resultType;
    }
    stmt.getVarValue()->accept(*this);
    if (!varType.empty() && varType != resultType) {
        throw TypeError("Incompatible type when initializing type '" + varType + " with type '" + resultType + "'", stmt.getToken());
    }
    // add to symbol table
    varSymbolTable[varName] = resultType;
}

void StaticAnalyzer::visit(const ParallelAssignmentStmt &stmt) {
    // TODO: Add support to unpack tuple

}

void StaticAnalyzer::visit(const ParamDeclStmt &stmt) {
    string paramName = dynamic_cast<IdentifierExpr&>(*stmt.getParamName()).getToken().Value;
    // If variable is already declared, we shadow it

    // TODO: Support generic
    string paramType;
    if (stmt.getParamType() != nullptr) {
        stmt.getParamType()->accept(*this);
        paramType = resultType;
    }
    stmt.getParamValue()->accept(*this);
    if (!paramType.empty() && paramType != resultType) {
        throw TypeError("Incompatible type when initializing type '" + paramType + " with type '" + resultType + "'", stmt.getToken());
    }
    // add to symbol table
    varSymbolTable[paramName] = resultType;
}

// TODO: Support generic procedure
void StaticAnalyzer::visit(const ProcDeclStmt &stmt) {
    string procName = dynamic_cast<IdentifierExpr&>(*stmt.getProcName()).getToken().Value;

    if (funcSymbolTable.find(procName) != funcSymbolTable.end()) {
        // check if it is overloading procedure
        auto funcFind = funcSymbolTable.equal_range(procName);
        // loop through all function
        bool isDeclared = false;
        //
        for (auto func = funcFind.first; func != funcFind.second; ++func) {
            auto paramList = func->second.paramList;
            if (paramList.size() == stmt.getParamList().size()) {
                int i = 0;
                for (i = 0; i < paramList.size(); i++) {
                    // Get type of param
                    stmt.getParamList()[i]->accept(*this);
                    // Compare with other function
                    if (paramList[i].type != resultType) {
                        break;
                    }
                }

                if (i == paramList.size()) isDeclared = true;
            }
            if (isDeclared)
                throw TypeError("Redeclaration of procedure '" + procName + "'", stmt.getToken());
        }
    }

    // Check params
    for (auto &x : stmt.getParamList()) {
        x->accept(*this);
    }
    // Check if params that have default values are located at the end of param list
    for (auto i = 0; i < stmt.getParamList().size(); i++) {
        auto& currentParam = dynamic_cast<ParamDeclStmt&>(*stmt.getParamList()[i]);
        auto paramToken = dynamic_cast<IdentifierExpr&>(*currentParam.getParamName()).getToken();
        if (i > 0 && dynamic_cast<ParamDeclStmt&>(*stmt.getParamList()[i - 1]).getParamValue() != nullptr
            && currentParam.getParamValue() == nullptr) {
            throw TypeError("Missing default value on parameter '" + paramToken.Value + "'", paramToken);
        }
    }
    // Check body
    stmt.getBody()->accept(*this);
}

void StaticAnalyzer::visit(const BlockStmt &stmt) {
    stmt.getStmts()->accept(*this);
}

void StaticAnalyzer::visit(const ProgramRoot &root) {
    for (auto &stmt : root.getProgramBody()) {
        stmt->accept(*this);
    }
}

void StaticAnalyzer::visit(const IfStmt &stmt) {
    stmt.getCondExpr()->accept(*this);
    if (resultType != "Bool") {
        throw TypeError("Unable to cast type '" + resultType + "' to 'Bool'", stmt.getToken());
    }
    stmt.getIfBlock()->accept(*this);

    if (stmt.getElseBlock() != nullptr)
        stmt.getElseBlock()->accept(*this);
}

void StaticAnalyzer::visit(const CallExpr &expr) {

}

void StaticAnalyzer::visit(const CallStmt &stmt) {

}

void StaticAnalyzer::visit(const ForStmt &stmt) {
    
}

void StaticAnalyzer::visit(const RangeExpr &expr) {

}
