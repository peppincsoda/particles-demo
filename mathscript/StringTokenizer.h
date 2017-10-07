#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include "TokenizerInterface.h"

namespace mathscript {

    class StringTokenizer : public TokenizerInterface
    {
    public:
        explicit StringTokenizer(const std::string& src_str);
        explicit StringTokenizer(std::string&& src_str);
        ~StringTokenizer();

        StringTokenizer(const StringTokenizer&) = delete;
        StringTokenizer& operator=(const StringTokenizer&) = delete;

        StringTokenizer& operator >> (Token& token);

        void ReadToken(Token& token) override;

    private:
        int stream_get();
        void stream_unget();

        static void CreateNumberToken(Token& token);

        std::string src_str_;
        std::size_t position_;
        bool unget_called_;
        int last_ch_;
    };

}


#endif // STRINGTOKENIZER_H
