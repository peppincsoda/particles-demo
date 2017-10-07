#include "TokenType.h"

namespace mathscript {

    const char* TokenTypeStr(TokenType token_type)
    {
        switch (token_type) {
        case TokenType::Invalid: return "<invalid>";

        case TokenType::Plus:     return "+";
        case TokenType::Minus:    return "-";
        case TokenType::Asterisk: return "*";
        case TokenType::Slash:    return "/";
        case TokenType::Caret:    return "^";

        case TokenType::OpeningParent: return "(";
        case TokenType::ClosingParent: return ")";
        case TokenType::Comma:         return ",";

        case TokenType::Number:     return "<number>";
        case TokenType::Identifier: return "<identifier>";

        case TokenType::EndOfStream: return "<end-of-stream>";

        default: return "<???>";
        }
    }

}
