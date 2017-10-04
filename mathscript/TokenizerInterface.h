#ifndef TOKENIZERINTERFACE_H
#define TOKENIZERINTERFACE_H

#include "TokenType.h"

#include <string>

namespace mathscript {

    struct Token
    {
        TokenType type;
        int column;

        std::string str_val;
        double dbl_val;
    };

    class TokenizerInterface
    {
    public:
        virtual ~TokenizerInterface() {}
        virtual void ReadToken(Token& token) = 0;
    };

}

namespace std {
template<>
    struct hash<mathscript::TokenType>
    {
        size_t operator()(mathscript::TokenType val) const noexcept
        {
            return static_cast<size_t>(val);
        }
    };
}

#endif // TOKENIZERINTERFACE_H
