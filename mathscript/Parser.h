#ifndef PARSER_H
#define PARSER_H

#include "TokenizerInterface.h"
#include "STNode.h"

#include <memory>

namespace mathscript {

    //! Parser builds the AST from the stream of tokens.
    class Parser
    {
    public:
        //! Construct a parser and bind it to the tokenizer.
        explicit Parser(TokenizerInterface& tokenizer);
        ~Parser();

        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        //! Parse the token stream and return the root node of the AST.
        std::unique_ptr<STNode> ParseInput();

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;
    };

}


#endif // PARSER_H
