#pragma once

#include "prefix.h"

namespace HLang
{
    class ParenthesesParse : public IPrefix {
    public:
        PExprNode parse(ExprParser& parser, Token token) override;
    };
}

