#include "StringTokenizer.h"

#include <sstream>

#include <cassert>

using namespace std;

namespace mathscript {

    StringTokenizer::StringTokenizer(const std::string& src_str)
        : src_str_(src_str)
        , position_(0)
        , unget_called_(false)
        , last_ch_(0)
    {

    }

    StringTokenizer::StringTokenizer(std::string&& src_str)
        : src_str_(std::move(src_str))
        , position_(0)
        , unget_called_(false)
        , last_ch_(0)
    {

    }

    StringTokenizer::~StringTokenizer()
    {

    }

    StringTokenizer& StringTokenizer::operator >> (Token& token)
    {
        ReadToken(token);
        return *this;
    }

    int StringTokenizer::stream_get()
    {
        if (unget_called_) {
            unget_called_ = false;
            return last_ch_;
        }

        int ch;
        if (position_ >= src_str_.length()) {
            ch = EOF;
        } else {
            ch = src_str_[position_++];
        }
        last_ch_ = ch;
        return ch;
    }

    void StringTokenizer::stream_unget()
    {
        unget_called_ = true;
    }

    void StringTokenizer::ReadToken(Token& token)
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

                if (c == EOF) {
                    token.type = TokenType::EndOfStream;
                    return;
                }

                token.str_val += c;

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
                    state = State::IntPart;
                } else if (c == '.') {
                    state = State::Dot;
                } else if ( ('A' <= c && c <= 'Z')
                         || ('a' <= c && c <= 'z')
                         || (c == '_') ) {
                    state = State::Ident;
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
                    stream_unget();
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

    void StringTokenizer::CreateNumberToken(Token& token)
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
