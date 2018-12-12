#pragma once

#include "token.h"
#include <vector>
#include <algorithm>

namespace HLang
{
    class TokenStream {
    public:
        Token getCurrent() const {
            return stream[currentIndex];
        }

        Token peek(int distance = 1) const {
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
        size_t currentIndex{UINT64_MAX};
        std::vector<Token> stream;
    };
}
