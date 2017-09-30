#ifndef STREAMTOKENIZER_H
#define STREAMTOKENIZER_H

#include <string>

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

    struct Token
    {
        TokenType type;
        int column;

        std::string str_val;
        double dbl_val;
    };

    class StreamTokenizer
    {
    public:
        explicit StreamTokenizer(std::istream& input_stream);
        ~StreamTokenizer();

        StreamTokenizer(const StreamTokenizer&) = delete;
        StreamTokenizer& operator=(const StreamTokenizer&) = delete;

        StreamTokenizer& operator >> (Token& token);

    private:
        int stream_get();
        void stream_unget();

        void ReadToken(Token& token);

        static void CreateNumberToken(Token& token);

        std::istream& input_stream_;
        std::size_t position_;
        bool unget_called_;
        int last_ch_;
    };

}


#endif // STREAMTOKENIZER_H
