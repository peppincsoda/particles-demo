#ifndef PARSER_H
#define PARSER_H

#include "TokenizerInterface.h"
#include "STNode.h"

#include <memory>

namespace mathscript {

    class Parser
    {
    public:
        explicit Parser(TokenizerInterface& tokenizer);
        ~Parser();

        Parser(const Parser&) = delete;
        Parser& operator=(const Parser&) = delete;

        std::unique_ptr<STNode> ParseInput();

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;
    };

}


#endif // PARSER_H
