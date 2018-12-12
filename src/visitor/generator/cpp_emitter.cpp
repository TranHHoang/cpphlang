
#include <hlang/visitor/generator/cpp_emitter.h>

#include "hlang/visitor/generator/cpp_emitter.h"
using namespace HLang;

void CppEmitter::emitRaw(const std::string &value, Opcode opcode) {
    switch (opcode) {
        case Opcode::Normal:
            outStream << value;
            break;
        case Opcode::Operator:
            outStream << " " << value << " ";
            break;
        case Opcode::CppKeyword:
        case Opcode::TypeDecl:
            outStream << value << " ";
            break;
    }
}

void CppEmitter::includeCppStdLib(const std::string &lib) {
    std::string includeLib = "#include <" + lib + ">\n";
    // insert at the start
    outStream.seekp(0);
    outStream.write(includeLib.c_str(), includeLib.size());
    // reset position
    outStream.seekp(0, std::ios::end);
}

void CppEmitter::createObject(const std::string &objType, const std::string& objName, const std::vector<std::string>& args) {
    outStream << objType << " " << objName;

    if (!args.empty()) {
        outStream << "(";
        for (auto i = 0; i < args.size(); i++) {
            outStream << args[i];
            if (i != args.size()) {
                outStream << ",";
            }
        }
        outStream << ")";
    }
}
