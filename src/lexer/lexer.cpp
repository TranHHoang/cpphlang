#include "../../include/hlang/lexer/lexer.h"
#include "../../include/hlang/utils/char_helper.h"
#include "../../include/hlang/error/syntax_error.h"
#include "hlang/lexer/lexer.h"
#include <unordered_map>
#include <regex>
#include <iostream>

using namespace HLang;
using std::string;

// --
#define OperatorMapContains(x) (OperatorMap.find(x) != OperatorMap.end())
#define NewToken(type, string) Token({fileReader.getPathName(), type, string, line, column})
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
        if (!CharHelper::isIdentifier(fileReader.peekChar())) break;
        value += nextChar();
    }

    return KeywordMap.find(value) == KeywordMap.end()
        ? Token({fileReader.getPathName(), TokenType::Identifier, value, line, column - value.length() + 1})
        : Token({fileReader.getPathName(), KeywordMap.find(value)->second, value, line, column - value.length() + 1});
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
                value += nextChar();
            }
            else if (CharHelper::isUniqueRealLiteral(c)) {
                return parseReal(value);
            }
            else break;
        }

        // Validating integer using regex
        if (std::regex_match(value, std::regex(IntegerRegexPattern))) {
            return NewToken(TokenType::IntLiteral, value);
        }
        throw SyntaxError(fileReader.getPathName(), "Invalid integer number '" + value + "'", line, column);
    }
}

Token Lexer::parseReal(const std::string &parsedValue) {
    string tempVal{nextChar()};
    bool hasPlusOrMinus = false;

    while (!fileReader.isEof()) {
        char peekChar = fileReader.peekChar();
        if (CharHelper::isUniqueRealLiteral(peekChar)
            || CharHelper::isNumberLiteral(peekChar)
            || ((peekChar == '+' || peekChar == '-') && not hasPlusOrMinus)) {
            hasPlusOrMinus = peekChar == '+' || peekChar == '-';
            tempVal += nextChar();
        }
        else break;
    }

    // Validating string using regex
    if (std::regex_match(parsedValue + tempVal, std::regex(FloatRegexPattern))) {
        return NewToken(TokenType::DoubleLiteral, parsedValue + tempVal);
    }
    throw SyntaxError(fileReader.getPathName(), "Invalid double number '" + parsedValue + tempVal + "'", line, column);
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

    return Token({
        fileReader.getPathName(),
        prefix == 2 ? TokenType::BinLiteral :
        prefix == 8 ? TokenType::OctLiteral :
        TokenType::HexLiteral,
        value,
        line,
        column - value.length() - BasePrefixLength
    });
}

Token Lexer::parseString() {
    string value;

    while (!fileReader.isEof())
    {
        if (fileReader.peekChar() == '"' || fileReader.peekChar() == '\n') break;
        value += nextChar();
    }
    nextChar(); // Skip close quote '"'

    return Token({fileReader.getPathName(), TokenType::StringLiteral, value, line, column - value.length()});
}

int Lexer::getIndentLevel() {
    int depth = 0;
    while (!fileReader.isEof() && (fileReader.peekChar() == '\t' || fileReader.peekChar() == ' ')) {
        if ((fileReader.peekChar() == '\t' && indentMarker == IndentMarker::Space)
            || (fileReader.peekChar() == ' ' && indentMarker == IndentMarker::Tab)) {
            throw SyntaxError(
                    fileReader.getPathName(),
                    "Inconsistent indentation marker: Expected '" + string(indentMarker == Space ? "Space" : "Tab") + "' but '" + string(1 - indentMarker == Space ? "Space" : "Tab") + "' found.",
                    line, column
            );
        }
        else if (indentMarker == IndentMarker::Undefined) {
            indentMarker = fileReader.peekChar() == '\t' ? IndentMarker::Tab : IndentMarker::Space;
        }
        nextChar();
        ++depth;
    }
    return depth;
}

void Lexer::start() {
    try {
        int previousDepth = 0;
        int totalDepth = 0;

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
                    case '\n': {
                        nextChar();

                        int currentDepth = getIndentLevel();
                        if (currentDepth != previousDepth) {
                            totalDepth += currentDepth > previousDepth ? 1 : -1;
                            tokenStream.append(Token({
                                fileReader.getPathName(),
                                currentDepth > previousDepth ? TokenType::Indent : TokenType::Dedent,
                                "",
                                line,
                                column
                            }));
                            previousDepth = currentDepth;
                        }

                        ++line;
                        column = 0;
                        break;
                    }
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
                                fileReader.getPathName(),
                                OperatorMap.find(actualOperator)->second,
                                actualOperator,
                                line,
                                column - actualOperator.length()
                            }));
                        }
                        else {
//                            fileReader.unread();
                            throw SyntaxError(fileReader.getPathName(), "Unknown character '" + actualOperator + "'", line, column);
                        }
                    }
                    break;
                }
            }
        }
        // Insert missing dedent
        while (totalDepth --> 0)
            tokenStream.append(NewToken(TokenType::Dedent, ""));
        // Insert end of source
        tokenStream.append(NewToken(TokenType::EndOfStream, ""));
    }
    catch (const SyntaxError& e) {
//        std::cerr << e.what();
        throw;
    }
}

