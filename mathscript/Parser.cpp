#include "Parser.h"
#include "Exception.h"

#include <vector>
#include <stack>
#include <algorithm> // reverse
#include <unordered_map>
#include <sstream>

using namespace std;

namespace mathscript {

    class Parser::Impl
    {
    public:
        explicit Impl(TokenizerInterface& tokenizer);
        ~Impl();

        std::unique_ptr<STNode> ParseInput();

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

    Parser::Parser(TokenizerInterface& tokenizer)
        : pimpl_(std::make_unique<Parser::Impl>(tokenizer))
    {
    }

    Parser::~Parser()
    {

    }

    std::unique_ptr<STNode> Parser::ParseInput()
    {
        return pimpl_->ParseInput();
    }

    Parser::Impl::Impl(TokenizerInterface& tokenizer)
        : tokenizer_(tokenizer)
    {

    }

    Parser::Impl::~Impl()
    {

    }

    static bool IsUnaryOp(TokenType token_type)
    {
        switch (token_type) {
            case TokenType::Plus:
            case TokenType::Minus:
                return true;
            default:
                return false;
        }
    }

    static bool IsBinaryOp(TokenType token_type)
    {
        switch (token_type) {
            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Asterisk:
            case TokenType::Slash:
            case TokenType::Caret:
                return true;
            default:
                return false;
        }
    }

    static bool IsOpBefore(TokenType op1, TokenType op2)
    {
        static std::unordered_map<TokenType, int> precedence_ =
        {
            {TokenType::Plus    , 1},
            {TokenType::Minus   , 1},
            {TokenType::Asterisk, 2},
            {TokenType::Slash   , 2},
            {TokenType::Caret   , 3},
        };

        enum class Associativity
        {
            Left,
            Right,
        };

        static std::unordered_map<TokenType, Associativity> associativity_ =
        {
            {TokenType::Plus    , Associativity::Left },
            {TokenType::Minus   , Associativity::Left },
            {TokenType::Asterisk, Associativity::Left },
            {TokenType::Slash   , Associativity::Left },
            {TokenType::Caret   , Associativity::Right},
        };

        if (op1 == op2) {
            if (associativity_[op1] == Associativity::Left)
                return true;
            else if (associativity_[op1] == Associativity::Right)
                return false;
        }

        return precedence_[op1] >= precedence_[op2];
    }

    void Parser::Impl::ReadToken()
    {
        tokenizer_.ReadToken(curr_token_);
    }

    void Parser::Impl::ExpectToken(TokenType token_type)
    {
        if (curr_token_.type == token_type) {
            ReadToken();
        } else {
            std::ostringstream os;
            os << "Expected token '" << TokenTypeStr(token_type) << "'";
            throw ParserException(curr_token_.column, os.str());
        }
    }

    bool Parser::Impl::AcceptToken(TokenType token_type)
    {
        if (curr_token_.type == token_type) {
            ReadToken();
            return true;
        }
        return false;
    }

    /**
     * @brief Parser::ParseInput
     * INPUT = EXPR, <end-of-stream>
     * @return
     */
    unique_ptr<STNode> Parser::Impl::ParseInput()
    {
        ReadToken();

        unique_ptr<STNode> expr(ParseExpr());
        ExpectToken(TokenType::EndOfStream);
        return expr;
    }

    /**
     * @brief Convert the expression to Reverse Polish notation (RPN) using the Shunting-yard algorithm.
     * @param [in,out] items The array representing the expression.
     */
    static void ConvertToRPN(vector<STExpr::Item>& items)
    {
        stack<STExpr::Item> ops;
        auto outit = begin(items);
        for (auto it = begin(items); it != end(items); ++it) {
            if (it->type == STExpr::Item::Type::Term) {
                *outit++ = *it;
            } else {
                while (!ops.empty() && IsOpBefore(ops.top().op, it->op)) {
                    *outit++ = ops.top();
                    ops.pop();
                }
                ops.push(*it);
            }
        }
        while (!ops.empty()) {
            *outit++ = ops.top();
            ops.pop();
        }
    }

    /**
     * @brief Reverse the order of the operands in the RPN.
     * @param [in,out] first,last
     *                 Iterators of the range to be reversed.
     */
    static void Reverse(vector<STExpr::Item>::iterator first, vector<STExpr::Item>::iterator last)
    {
        --last;
        if (last->type == STExpr::Item::Type::Term)
            return;

        // Find the first item of the second part
        auto it = last;
        auto size = 1;
        while (size > 0) {
            --it;
            if (it->type == STExpr::Item::Type::Term)
                size--;
            else
                size++;
        }

        Reverse(first, it);
        Reverse(it, last);

        // Swap the two parts of the vector using a temporary vector
        vector<STExpr::Item> first_part(first, it);
        auto next_it = copy(it, last, first);
        copy(begin(first_part), end(first_part), next_it);
    }

    /**
     * @brief Parser::ParseExpr
     * EXPR = TERM, {binop, TERM}
     * @return
     */
    unique_ptr<STExpr> Parser::Impl::ParseExpr()
    {
        auto expr = make_unique<STExpr>();
        expr->AddTerm(ParseTerm());
        while (IsBinaryOp(curr_token_.type)) {
            expr->AddOp(curr_token_.type);
            ReadToken();
            expr->AddTerm(ParseTerm());
        }

        ConvertToRPN(expr->items_);
        Reverse(begin(expr->items_), end(expr->items_));

        return expr;
    }

    /**
     * @brief Parser::ParseTerm
     * TERM = {unop}, ( number | IDENT | "(", EXPR, ")" )
     * @return
     */
    unique_ptr<STTerm> Parser::Impl::ParseTerm()
    {
        auto term = make_unique<STTerm>();

        while (IsUnaryOp(curr_token_.type)) {
            term->unary_ops_.push_back(curr_token_.type);
            ReadToken();
        }
        reverse(begin(term->unary_ops_), end(term->unary_ops_));

        if (curr_token_.type == TokenType::Number) {
            auto num = make_unique<STNum>();
            num->dbl_val_ = curr_token_.dbl_val;
            term->operand_ = move(num);
            ReadToken();

        } else if (curr_token_.type == TokenType::Identifier) {
            term->operand_ = ParseIdent();

        } else if (AcceptToken(TokenType::OpeningParent)) {
            term->operand_ = ParseExpr();
            ExpectToken(TokenType::ClosingParent);

        } else {
            std::ostringstream os;
            os << "Unexpected token '" << curr_token_.str_val << "'";
            throw ParserException(curr_token_.column, os.str());
        }

        return term;
    }

    /**
     * @brief Parser::ParseIdent
     * IDENT = ident, [ "(", [ EXPR, {",", EXPR} ], ")" ]
     * @return
     */
    unique_ptr<STFunc> Parser::Impl::ParseIdent()
    {
        auto func = make_unique<STFunc>();

        const auto& ident = curr_token_.str_val;
        func->name_ = ident;
        ReadToken();

        if (AcceptToken(TokenType::OpeningParent)) {
            if (!AcceptToken(TokenType::ClosingParent)) {
                func->params_.push_back(ParseExpr());
                while (curr_token_.type == TokenType::Comma) {
                    ReadToken();
                    func->params_.push_back(ParseExpr());
                }
                reverse(begin(func->params_), end(func->params_));
                ExpectToken(TokenType::ClosingParent);
            }
        }

        return func;
    }
}
