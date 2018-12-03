#include "../../include/hlang/lexer/lexer.h"
#include "../../include/hlang/utils/char_helper.h"
#include "../../include/hlang/error/syntax_error.h"
#include <unordered_map>
#include <regex>
#include <iostream>

using namespace HLang;
using std::string;

// --
#define OperatorMapContains(x) (OperatorMap.find(x) != OperatorMap.end())
// --

char Lexer::nextChar() {
    ++column;
    return fileReader.nextChar();
}

void Lexer::unread() {
    --column;
    fileReader.unread();
}

Token Lexer::parseIdentifier() {
    string value;

    while (!fileReader.isEof()) {
        if (CharHelper::isIdentifier(fileReader.peekChar())) break;
        value += nextChar();
    }

    return KeywordMap.count(value) == 0
        ? Token({TokenType::Identifier, value, line, column})
        : Token({KeywordMap.find(value)->second, value, line, column});
}

Token Lexer::parseNumber() {
    string value;
    char c = nextChar();

    if (c == '0' && CharHelper::isBasePrefix(fileReader.peekChar())) {
        return parseNumberWithBase(nextChar());
    }
    else if (c == '.') {
        return parseReal(std::to_string(c));
    }
    else { // Just a normal integer in base 10
        value += c;
        while (!fileReader.isEof()) {
            c = fileReader.peekChar();
            if (CharHelper::isNumberLiteral(c)) {
                value += c;
            }
            else if (CharHelper::isUniqueRealLiteral(c)) {
                return parseReal(value);
            }
            else break;
        }

        // Validating string using regex
        if (std::regex_match(value, std::regex(IntegerRegexPattern))) {
            return Token({TokenType::IntLiteral, value, line, column});
        }
        throw SyntaxError("Invalid integer number '" + value + "'", line, column);
    }
}

Token Lexer::parseReal(const std::string &parsedValue) {
    string tempVal = std::to_string(nextChar());
    bool hasPlusOrMinus = false;

    while (!fileReader.isEof()) {
        char peekChar = fileReader.peekChar();
        if (CharHelper::isUniqueRealLiteral(peekChar)
            || CharHelper::isNumberLiteral(peekChar)
            || peekChar == '+' || peekChar == '-'
            || not hasPlusOrMinus) {
            hasPlusOrMinus = peekChar == '+' || peekChar == '-';
            tempVal += nextChar();
        }
        else break;
    }

    // Validating string using regex
    if (std::regex_match(parsedValue + tempVal, std::regex(FloatRegexPattern))) {
        return Token({TokenType::DoubleLiteral, parsedValue + tempVal, line, column});
    }
    throw SyntaxError("Invalid double number '" + parsedValue + tempVal + "'", line, column);
}

Token Lexer::parseNumberWithBase(char prefix) {
    string value;

    prefix = (char)tolower(prefix);

    while (!fileReader.isEof()) {
        if ((prefix == 'b' && CharHelper::isBin(fileReader.peekChar()))
            || (prefix == 'o' && CharHelper::isOct(fileReader.peekChar()))
            || (prefix == 'x' && CharHelper::isHex(fileReader.peekChar()))) {
            value += nextChar();
        }
        else break;
    }

    return Token({prefix == 2 ? TokenType::BinLiteral :
                 prefix == 8 ? TokenType::OctLiteral :
                 TokenType::HexLiteral,
                 value,
                 line,
                 column - value.length() - BasePrefixLength});
}

Token Lexer::parseString() {
    string value;

    while (!fileReader.isEof())
    {
        if (fileReader.peekChar() == '"' || fileReader.peekChar() == '\n') break;
        value += nextChar();
    }
    nextChar(); // Skip close quote '"'

    return Token({TokenType::DoubleQuote, value, line, column - value.length()});
}

void Lexer::start() {
    try {
        while (!fileReader.isEof()) {
            char currentChar = fileReader.peekChar();
            if (CharHelper::isStartOfIdentifier(currentChar)) {
                tokenStream.append(parseIdentifier());
            }
            else if (isdigit(currentChar)
                || (currentChar == '.' && isdigit(fileReader.peekChar()))) {
                tokenStream.append(parseNumber());
            }
            else {
                switch (currentChar) {
                    case '\n':
                        nextChar();
                        ++line;
                        column = 0;
                        break;
                    case '"':
                        nextChar();
                        tokenStream.append(parseString());
                        break;
                    default: {
                        if (isspace(currentChar)) {
                            nextChar();
                            continue;
                        }

                        string actualOperator{nextChar()};

                        if (OperatorMapContains(actualOperator)
                        || OperatorMapContains(actualOperator + fileReader.peekChar())) {
                            if (OperatorMapContains(actualOperator + fileReader.peekChar())) {
                                actualOperator += nextChar();
                            }

                            tokenStream.append(Token({
                                OperatorMap.find(actualOperator)->second,
                                actualOperator,
                                line,
                                column - actualOperator.length()
                            }));
                        }
                        else {
//                            fileReader.unread();
                            throw SyntaxError("Unknown character '" + actualOperator + "'", line, column);
                        }
                    }
                    break;
                }
            }
        }
        tokenStream.append(Token({TokenType::EndOfStream, "", line, column}));
    }
    catch (const SyntaxError& e) {
        std::cerr << e.what();
    }
}


