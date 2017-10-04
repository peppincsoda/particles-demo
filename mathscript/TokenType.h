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
}


#endif // TOKENTYPE_H
