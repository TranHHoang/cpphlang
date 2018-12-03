#pragma once

#include <vector>
#include <algorithm>
#include "token.h"

namespace HLang
{
    class TokenStream {
    public:
        Token getCurrent() {
            return stream[currentIndex];
        }

        Token peek(int distance = 1) {
            return stream[std::min(currentIndex + distance, stream.size())];
        }

        Token getNext() {
            return stream[std::min(++currentIndex, stream.size())];
        }

        void unread() {
            --currentIndex;
        }

        void append(Token token) {
            stream.push_back(token);
        }
    private:
        size_t currentIndex{0};
        std::vector<Token> stream;
    };
}
