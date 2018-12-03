#pragma once
#include <cctype>

namespace HLang
{
    namespace CharHelper
    {
        inline bool isStartOfIdentifier(char c) {
            return isalpha(c) || c == '_';
        }

        inline bool isIdentifier(char c) {
            return isalnum(c) || c == '_';
        }

        inline bool isBasePrefix(char c) {
            c = tolower(c);
            return c == 'b' || c == 'o' || c == 'x';
        }

        inline bool isNumberLiteral(char c) {
            return isdigit(c) || c == '_';
        }

        inline bool isUniqueRealLiteral(char c) {
            return c == 'e' || c == 'E' || c == '.';
        }

        inline bool isBin(char c) {
            return c == '0' || c == '1';
        }

        inline bool isOct(char c) {
            return c >= '0' && c <= '7';
        }

        inline bool isHex(char c) {
            c = tolower(c);
            return isdigit(c) || (c >= 'a' && c <= 'f');
        }

        inline bool isDigit(char c) {
            return isdigit(c);
        }
    }
}