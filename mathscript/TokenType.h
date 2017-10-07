#ifndef TOKENTYPE_H
#define TOKENTYPE_H


namespace mathscript {

    enum class TokenType
    {
        Invalid,

        Plus,
        Minus,
        Asterisk,
        Slash,
        Caret,

        OpeningParent,
        ClosingParent,
        Comma,

        Number,
        Identifier,

        EndOfStream,
    };

    const char* TokenTypeStr(TokenType token_type);
}


#endif // TOKENTYPE_H
