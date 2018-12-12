#pragma once
#include "hlang/token/token.h"
#include <vector>
#include <string>
#include <sstream>

// Using C++17 standard
namespace HLang
{
    enum class Opcode {
        Normal, Operator, CppKeyword, TypeDecl,
    };

    class CppEmitter {
    public:
        CppEmitter(std::ostream& outStream) : outStream(outStream) { }

        void includeCppStdLib(const std::string &lib);
        void emitRaw(const std::string &value, Opcode opcode = Opcode::Normal);

        void createObject(const std::string &objType, const std::string& objName, const std::vector<std::string>& args);

    private:
        std::ostream &outStream;
    };
}