#pragma once

#include <string>

namespace HLang
{
    class ReadonlyFileStream
    {
    public:
        ReadonlyFileStream(const std::string& name, std::istream& stream)
            : name(name), stream(stream) { }
        ReadonlyFileStream(const ReadonlyFileStream& stream)
            : name(stream.name), stream(stream.stream) { }

        char nextChar() { return stream.get(); }
        char peekChar() { return stream.peek(); }
        bool isEof() { return stream.eof(); }
        void unread() { stream.unget(); }
    private:
        std::string name;
        std::istream& stream;
    };
}