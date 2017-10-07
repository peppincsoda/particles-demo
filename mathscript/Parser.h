#ifndef PARSER_H
#define PARSER_H

#include "TokenizerInterface.h"
#include "STNode.h"

#include <memory>
#include <unordered_map>

namespace mathscript {

    class Parser
    {
    public:
        explicit Parser(TokenizerInterface& tokenizer);
        ~Parser();

        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        std::unique_ptr<STNode> ParseInput();

        void RegisterFunc(const std::string& name, int num_params);

    private:
        void ReadToken();
        void ExpectToken(TokenType token_type);
        bool AcceptToken(TokenType token_type);

        std::unique_ptr<STExpr> ParseExpr();
        std::unique_ptr<STTerm> ParseTerm();
        std::unique_ptr<STFunc> ParseIdent();

        TokenizerInterface& tokenizer_;

        Token curr_token_;
    };

}


#endif // PARSER_H
