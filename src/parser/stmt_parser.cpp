#include "hlang/parser/stmt_parser.h"
#include "hlang/error/parse_error.h"
#include "hlang/parser/expr/expr_headers.h"
#include "hlang/parser/stmt_parser.h"
#include <vector>
#include <hlang/error/syntax_error.h>
#include <hlang/parser/stmt_parser.h>


using namespace HLang;

PStmtNode StmtParser::parseProgram() {
    std::vector<PStmtNode> stmtList;
    while (true) {
        auto token = exprParser.getTokenStream().peek();
        switch (token.Type) {
            case TokenType::Var:
                stmtList.push_back(parseVar());
                break;
            case TokenType::Call:
                stmtList.push_back(parseCall());
                break;
//            case TokenType::Indent:
//                stmtList.push_back(parseBlock());
//                break;
            case TokenType::Proc:
                stmtList.push_back(parseProc());
                break;
            case TokenType::EndOfStream:
                return std::make_unique<ProgramRoot>(token, std::move(stmtList));
            default:
                throw SyntaxError("Invalid syntax, used '" + token.Value + "' outside of block", token);
        }
    }
}

// TODO: VarToken may not needed in compound statement
PStmtNode StmtParser::parseVar() {
    auto varToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Var);

    std::vector<PStmtNode> declList;

    while (true) {
        auto varNameToken = exprParser.getTokenStream().peek();
        exprParser.consume(TokenType::Identifier);
        auto varName = std::make_unique<IdentifierExpr>(varNameToken);

        PExprNode varType = nullptr;

        auto currentTok = exprParser.getTokenStream().peek();

        switch (currentTok.Type) {
            case TokenType::Assign:
                break;
            case TokenType::Comma:
                // Unpack and declare: var a, b, c = unpack(), unpack()
                break;
            case TokenType::Colon: {
                exprParser.consume(TokenType::Colon);

                auto varTypeTok = exprParser.getTokenStream().peek();
                exprParser.consume(TokenType::Identifier);

                varType = std::make_unique<IdentifierExpr>(varTypeTok);
                break;
            }
            default:
                throw ParseError("Expected ':' or '=', but '" + currentTok.Value + "' found", currentTok);
        }

        PExprNode initValue = nullptr;
        if (currentTok.Type == TokenType::Assign) {
            exprParser.consume(TokenType::Assign);
            initValue = exprParser.parse(0);
        }

        declList.push_back(std::make_unique<VarDeclStmt>(varToken, std::move(varName), std::move(varType), std::move(initValue)));

        if (exprParser.getTokenStream().peek().Type != TokenType::Comma) break;
        exprParser.consume(TokenType::Comma);
    }
    return std::make_unique<Statements>(varToken, std::move(declList));
}

PStmtNode StmtParser::parseSet() {
    // set a = b = 1
    // set a, b = 1, 2
    // set a, b = unpack()
    auto setToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Set);

    auto varNameToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Identifier);

    switch (exprParser.getTokenStream().peek().Type) {
        case TokenType::Assign:
            exprParser.consume(TokenType::Assign);
            return std::make_unique<AssignmentStmt>(
                setToken,
                std::make_unique<AssignmentExpr>(
                    varNameToken,
                    std::make_unique<IdentifierExpr>(varNameToken),
                    exprParser.parse((int)Precedence::Assignment - 1)
                )
            );
        case TokenType::Comma: {
            auto parseExprList = [&](vector<PExprNode>& list) {
                while (true) {
                    varNameToken = exprParser.getTokenStream().peek();
                    exprParser.consume(TokenType::Identifier);

                    list.push_back(std::make_unique<IdentifierExpr>(varNameToken));
                    if (exprParser.getTokenStream().peek().Type != TokenType::Comma) {
                        break;
                    }
                    exprParser.consume(TokenType::Comma);
                }
            };

            exprParser.consume(TokenType::Comma);

            vector<PExprNode> lhsList;
            lhsList.push_back(std::make_unique<IdentifierExpr>(varNameToken));

            parseExprList(lhsList);

            vector<PExprNode> rhsList;
            exprParser.consume(TokenType::Assign);

            parseExprList(rhsList);

            return std::make_unique<ParallelAssignmentStmt>(setToken, std::move(lhsList), std::move(rhsList));
        }
        default:
            break;
    }
}

PStmtNode StmtParser::parseBlock() {
    // var a = 1; set a = 2; call print(a)
    std::vector<PStmtNode> stmtList;
    exprParser.consume(TokenType::Indent); // start of block

    bool isDone = false;
    while (!isDone) {
        auto token = exprParser.getTokenStream().peek();
        switch (token.Type) {
//            case TokenType::Indent:
//                exprParser.consume(TokenType::Indent);
//                stmtList.push_back(parseBlock());
//                break;
            case TokenType::Var:
                stmtList.push_back(parseVar());
                break;
            case TokenType::Set:
                stmtList.push_back(parseSet());
                break;
            case TokenType::If:
                stmtList.push_back(parseIf());
                break;
            default:
                isDone = true;
                break;
        }
    }

    if (exprParser.getTokenStream().peek().Type == TokenType::Indent) {
        throw SyntaxError("Unexpected indent", exprParser.getTokenStream().peek());
    }
    else {
        exprParser.consume(TokenType::Dedent);
    }
    return std::make_unique<BlockStmt>(Token(), std::make_unique<Statements>(Token(), std::move(stmtList)));
}

PStmtNode StmtParser::parseProc() {
    // proc main(args = ''):
    auto procToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Proc);

    auto procNameToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Identifier);
    auto procName = std::make_unique<IdentifierExpr>(procNameToken);

    // parse parameters list
    exprParser.consume(TokenType::LeftParen);
    vector<PStmtNode> paramList;
    while (exprParser.getTokenStream().peek().Type != TokenType::RightParen) {
        // ([ref]a[:int][= 100])
        // TODO: Add support for 'ref' keyword
        auto paramNameTok = exprParser.getTokenStream().peek();
        exprParser.consume(TokenType::Identifier);
        PExprNode paramName = std::make_unique<IdentifierExpr>(procNameToken);
        PExprNode paramType = nullptr;
        PExprNode paramDefaultValue = nullptr;
        // if param do not have type as well as default value, we mark it as template
        switch (exprParser.getTokenStream().peek().Type) {
            case TokenType::Colon:
                exprParser.consume(TokenType::Colon);
                paramType = exprParser.parse(0);
                if (exprParser.getTokenStream().peek().Type == TokenType::Assign) {
                    exprParser.consume(TokenType::Assign);
                    paramDefaultValue = exprParser.parse(0);
                }
                break;
            case TokenType::Assign:
                paramDefaultValue = exprParser.parse(0);
                break;
            default:
                break;
        }

        paramList.push_back(std::make_unique<ParamDeclStmt>(
                paramName->getToken(),
                nullptr,
                std::move(paramName),
                std::move(paramType),
                std::move(paramDefaultValue)));

        if (exprParser.getTokenStream().peek().Type != TokenType::RightParen)
            exprParser.consume(TokenType::Comma);
    }
    exprParser.consume(TokenType::RightParen);
    exprParser.consume(TokenType::Colon);

    return std::make_unique<ProcDeclStmt>(procToken, std::move(procName), std::move(paramList), parseBlock());
}

PStmtNode StmtParser::parseCall() {
    // call main()
    auto callToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Call);

    auto callerFunc = exprParser.parse(0);

    exprParser.consume(TokenType::LeftParen);

    vector<PExprNode> argList;
    // TODO: Using named arguments
    while (exprParser.getTokenStream().peek().Type != TokenType::RightParen) {
        argList.push_back(exprParser.parse(0));

        if (exprParser.getTokenStream().peek().Type != TokenType::RightParen)
            exprParser.consume(TokenType::Comma);
    }

    exprParser.consume(TokenType::RightParen);

    return std::make_unique<CallStmt>(callToken, std::make_unique<CallExpr>(callToken, std::move(callerFunc), std::move(argList)));
}

PStmtNode StmtParser::parseIf() {
    auto ifToken = exprParser.getTokenStream().peek();

    exprParser.consume(ifToken.Type == TokenType::If ? TokenType::If : TokenType::Elif);

    auto ifCond = exprParser.parse(0);
    exprParser.consume(TokenType::Colon);

    auto ifBlock = parseBlock();

    if (exprParser.getTokenStream().peek().Type == TokenType::Else) {
        exprParser.consume(TokenType::Else);
        exprParser.consume(TokenType::Colon);
        return std::make_unique<IfStmt>(ifToken, std::move(ifCond), std::move(ifBlock), parseBlock());
    }
    else if (exprParser.getTokenStream().peek().Type == TokenType::Elif) {
        return std::make_unique<IfStmt>(ifToken, std::move(ifCond), std::move(ifBlock), parseIf());
    }
    else {
        return std::make_unique<IfStmt>(ifToken, std::move(ifCond), std::move(ifBlock), nullptr);
    }
}

PStmtNode StmtParser::parseFor() {
    auto forToken = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::For);

    auto iteratorVarTok = exprParser.getTokenStream().peek();
    exprParser.consume(TokenType::Identifier);

    exprParser.consume(TokenType::In);
    auto startRange = exprParser.parse(0);
    PExprNode endRange = nullptr;

    if (exprParser.getTokenStream().peek().Type == TokenType::Range) {
        exprParser.consume(TokenType::Range);
        endRange = exprParser.parse(0);
    }

    exprParser.consume(TokenType::Colon);

    return std::make_unique<ForStmt>(forToken,
            std::make_unique<IdentifierExpr>(iteratorVarTok),
            std::make_unique<RangeExpr>(startRange->getToken(), std::move(startRange), std::move(endRange)),
            parseBlock());
    // for i in 1..100: something => Range r(1, 100); r.loop([]() { something });
}

