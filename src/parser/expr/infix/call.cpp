#include "hlang/ast/ast_headers.h"
#include "hlang/parser/expr/infix/call.h"
#include "hlang/ast/expr/expression.h"
#include "hlang/parser/expr_parser.h"

namespace HLang
{
    PExprNode CallParse::parse(ExprParser &parser, PExprNode leftExpr, Token token) {
        auto funcNameToken = parser.getTokenStream().peek();
        auto callerFunc = parser.parse(0);

        parser.consume(TokenType::LeftParen);

        vector<PExprNode> argList;
        // TODO: Using named arguments
        while (parser.getTokenStream().peek().Type != TokenType::RightParen) {
            argList.push_back(parser.parse(0));

            if (parser.getTokenStream().peek().Type != TokenType::RightParen)
                parser.consume(TokenType::Comma);
        }

        parser.consume(TokenType::RightParen);

        return std::make_unique<CallExpr>(funcNameToken, std::move(callerFunc), std::move(argList));
    }
}