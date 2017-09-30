#include "StreamTokenizer.h"

#include <sstream>
#include <cassert>

using namespace std;

namespace mathscript {

    StreamTokenizer::StreamTokenizer(istream& input_stream)
        : input_stream_(input_stream)
        , position_(0)
        , unget_called_(false)
        , last_ch_(0)
    {

    }

    StreamTokenizer::~StreamTokenizer()
    {

    }

    StreamTokenizer& StreamTokenizer::operator >> (Token& token)
    {
        ReadToken(token);
        return *this;
    }

    int StreamTokenizer::stream_get()
    {
        if (unget_called_) {
            unget_called_ = false;
            return last_ch_;
        }

        const int ch = input_stream_.get();
        if (ch != EOF) {
            position_++;
        }
        last_ch_ = ch;
        return ch;
    }

    void StreamTokenizer::stream_unget()
    {
        unget_called_ = true;
    }

    void StreamTokenizer::ReadToken(Token& token)
    {
        enum class State
        {
            Start,
            IntPart,
            Dot,
            FracPart,
            Ident,
        };

        token.str_val.clear();

        auto state = State::Start;
        for (;;) {
            const auto c = stream_get();

            switch (state) {
            case State::Start:
                if (c == ' ' || c == '\t')
                    continue;

                token.column = position_;

                switch (c) {
                case '+': token.type = TokenType::Plus; return;
                case '-': token.type = TokenType::Minus; return;
                case '*': token.type = TokenType::Asterisk; return;
                case '/': token.type = TokenType::Slash; return;
                case '^': token.type = TokenType::Caret; return;
                case '(': token.type = TokenType::OpeningParent; return;
                case ')': token.type = TokenType::ClosingParent; return;
                case ',': token.type = TokenType::Comma; return;
                }

                if ('0' <= c && c <= '9') {
                    token.str_val += c;
                    state = State::IntPart;
                } else if (c == '.') {
                    token.str_val += c;
                    state = State::Dot;
                } else if ( ('A' <= c && c <= 'Z')
                         || ('a' <= c && c <= 'z')
                         || (c == '_') ) {
                    token.str_val += c;
                    state = State::Ident;
                } else if (c == EOF) {
                    token.type = TokenType::EndOfStream;
                    return;
                } else {
                    token.type = TokenType::Invalid;
                    return;
                }
                break;

            case State::IntPart:
                if ('0' <= c && c <= '9') {
                    token.str_val += c;
                } else if (c == '.') {
                    token.str_val += c;
                    state = State::Dot;
                } else {
                    stream_unget();
                    CreateNumberToken(token);
                    return;
                }
                break;

            case State::Dot:
                if ('0' <= c && c <= '9') {
                    token.str_val += c;
                    state = State::FracPart;
                } else {
                    token.type = TokenType::Invalid;
                    return;
                }
                break;

            case State::FracPart:
                if ('0' <= c && c <= '9') {
                    token.str_val += c;
                } else {
                    stream_unget();
                    CreateNumberToken(token);
                    return;
                }
                break;

            case State::Ident:
                if ( ('A' <= c && c <= 'Z')
                  || ('a' <= c && c <= 'z')
                  || (c == '_')
                  || ('0' <= c && c <= '9') ) {
                    token.str_val += c;
                } else {
                    stream_unget();
                    token.type = TokenType::Identifier;
                    return;
                }
                break;

            default:
                assert(0);
            }
        }
    }

    void StreamTokenizer::CreateNumberToken(Token& token)
    {
        std::istringstream stream(token.str_val);
        double val;
        stream >> val;
        if (stream.fail()) {
            token.type = TokenType::Invalid;
        } else {
            token.type = TokenType::Number;
            token.dbl_val = val;
        }
    }

}
