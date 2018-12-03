#pragma once

#include "prefix.h"

namespace HLang
{
    class LiteralParse : public IPrefix {
    public:
        PExprNode parse(ExprParser& parser, Token token) override;
    };
}