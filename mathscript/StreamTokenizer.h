#ifndef STREAMTOKENIZER_H
#define STREAMTOKENIZER_H

#include "TokenizerInterface.h"

namespace mathscript {

    class StreamTokenizer : public TokenizerInterface
    {
    public:
        explicit StreamTokenizer(std::istream& input_stream);
        ~StreamTokenizer();

        StreamTokenizer(const StreamTokenizer&) = delete;
        StreamTokenizer& operator=(const StreamTokenizer&) = delete;

        StreamTokenizer& operator >> (Token& token);

        void ReadToken(Token& token) override;

    private:
        int stream_get();
        void stream_unget();

        static void CreateNumberToken(Token& token);

        std::istream& input_stream_;
        std::size_t position_;
        bool unget_called_;
        int last_ch_;
    };

}


#endif // STREAMTOKENIZER_H
