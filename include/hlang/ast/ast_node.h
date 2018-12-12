#pragma once
#include "../token/token.h"
#include <memory>

namespace HLang
{
    class AbstractVisitor;

    class AstNode {
    protected:
        enum class NodeType {
            Expression,
            Statement,
        };
        NodeType getType() const { return nodeType; }

    public:
        AstNode(NodeType type, Token token) : token(std::move(token)), nodeType(type) { }
        virtual ~AstNode() = default;
        Token getToken() const { return token; }
        virtual void accept(AbstractVisitor&) = 0;

    private:
        Token token;
        NodeType nodeType;
    };
}

using PAstNode = std::unique_ptr<HLang::AstNode>;