#pragma once

#include <string>

namespace HLang
{
    class ReadonlyFileStream
    {
    public:
        ReadonlyFileStream(const std::string& name, std::istream& stream)
            : pathName(name), stream(stream) { }
        ReadonlyFileStream(const ReadonlyFileStream& stream)
            : pathName(stream.pathName), stream(stream.stream) { }

        char nextChar() const { return stream.get(); }
        char peekChar() const { return stream.peek(); }
        bool isEof() const { return stream.peek() == EOF; }
        void unread() const { stream.unget(); }
        std::string getPathName() const { return pathName; }
    private:
        std::string pathName;
        std::istream& stream;
    };
}