#pragma once
#include "../token/token.h"
#include <memory>

namespace HLang
{
    class AstVisitor;

    class AstNode {
    protected:
        enum class NodeType {
            Expression,
            Statement,
        };

    public:
        AstNode(NodeType type, Token token) : token(std::move(token)), nodeType(type) { }

        NodeType getType() const { return nodeType; }
        Token getToken() const { return token; }
        virtual void accept(AstVisitor&) = 0;

    private:
        Token token;
        NodeType nodeType;
    };

    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

using PAstNode = std::unique_ptr<HLang::AstNode>;