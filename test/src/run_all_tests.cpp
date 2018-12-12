#include "gtest/gtest.h"
#include "hlang/lexer/lexer.h"
#include "hlang/parser/expr_parser.h"
#include <iostream>
using namespace HLang;

TEST(HLang, SimpleAddLexer) {
    std::string fileName = "test.hl";
    std::stringstream stream;
    stream << "1e";
    HLang::ReadonlyFileStream fileStream(fileName, stream);

    HLang::Lexer lexer(fileStream);
    lexer.start();
    lexer.getTokenStream();
}

TEST(HLang, SimpleAddParser) {
    string fileName = "test.hl";
    std::stringstream stream;
    stream << "1+2*3";
    ReadonlyFileStream fileStream(fileName, stream);

    Lexer lexer(fileStream);
    lexer.start();
    ExprParser exprParser(lexer.getTokenStream());
    auto ast = exprParser.parse(0);
}