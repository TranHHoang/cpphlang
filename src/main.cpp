#include <iostream>
#include <sstream>
#include "../include/hlang/lexer/lexer.h"
#include "../include/hlang/utils/file_stream.h"

int main() {
    std::string fileName = "test.hl";
    std::stringstream stream;
    stream << ".e1";
    HLang::ReadonlyFileStream fileStream(fileName, stream);

    HLang::Lexer lexer(fileStream);
    lexer.start();
    lexer.getTokenStream();
    return 0;
}