#pragma once

#include "prefix.h"

namespace HLang
{
    class IdentifierParse : public IPrefix {
    public:
        PExprNode parse(ExprParser& parser, Token token) override;
    };
}
