#include <iostream>
#include <sstream>
#include "hlang/visitor/generator/cpp_gen.h"
#include "hlang/visitor/analyzer/analyzer.h"
#include "hlang/parser/stmt_parser.h"
#include "hlang/lexer/lexer.h"
#include "hlang/parser/expr_parser.h"
using namespace HLang;

int main() {
    string fileName = "test.hl";
    std::stringstream stream;
    // a = b ** c => a = b.operator_pow(c)
    stream << "proc main():\n\tif 1==3:\n\t\tvar a = 10\n\tif 2==3:\n\t\tvar b = 10";
    //cmake -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_TARGETS_TO_BUILD="host" -DLLVM_ENABLE_ASSERTIONS=ON -DCMAKE_BUILD_TYPE=Release ..
    ReadonlyFileStream fileStream(fileName, stream);

    try {
        Lexer lexer(fileStream);
        lexer.start();

        ExprParser exprParser(lexer.getTokenStream());
        StmtParser stmtParser(exprParser);

        auto ast = stmtParser.parseProgram();

        StaticAnalyzer analyzer;
        analyzer.visit(dynamic_cast<const ProgramRoot&>(*ast));

        std::ostringstream stream;
        CppGenerator generator(stream, analyzer);
        generator.visit(dynamic_cast<const ProgramRoot&>(*ast));
        std::cout << stream.str();
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}