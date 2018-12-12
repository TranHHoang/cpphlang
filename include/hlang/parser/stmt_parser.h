#pragma once
#include "hlang/ast/ast_headers.h"
#include "hlang/token/token_stream.h"
#include "hlang/parser/expr_parser.h"

namespace HLang
{
    class StmtParser {
    public:
//        StmtParser(TokenStream tokenStream) : exprParser(tokenStream) { }
        StmtParser(ExprParser& exprParser) : exprParser(exprParser) { }

        PStmtNode parseProgram();

    private:
        PStmtNode parseVar();
        PStmtNode parseSet();
        PStmtNode parseBlock();
        PStmtNode parseCall();
//
        PStmtNode parseProc();
//        PStmtNode parseFunc();
//
        PStmtNode parseIf();
        PStmtNode parseFor();
//        PStmtNode parseWhile();
//        PStmtNode parseCase();

        ExprParser& exprParser;
    };
}