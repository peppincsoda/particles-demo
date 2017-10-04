
#include "gtest/gtest.h"

#include "mathscript/TokenizerInterface.h"
#include "mathscript/Parser.h"
#include "mathscript/STNodePrintVisitor.h"

#include <sstream>

using namespace mathscript;

class MockTokenizer : public TokenizerInterface
{
public:
    MockTokenizer(std::initializer_list<Token> tokens)
        : tokens_(std::begin(tokens), std::end(tokens))
        , it_(std::cbegin(tokens_))
    {

    }

    void ReadToken(Token& token) override
    {
        if (it_ != std::cend(tokens_)) {
            token = *it_++;
        }
    }

private:
    const std::vector<Token> tokens_;
    std::vector<Token>::const_iterator it_;
};

static std::string PrintST(std::unique_ptr<STNode>&& node)
{
    std::ostringstream os;
    STNodePrintVisitor visitor(os);
    node->Visit(visitor);
    return os.str();
}

TEST(ParserTest, ReverseItems)
{
    MockTokenizer tokenizer({
        {TokenType::Number, 0, "1", 1},
        {TokenType::Plus  , 2, "+", 0},
        {TokenType::Number, 4, "2", 2},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(2)(1)+", str.c_str());
}

TEST(ParserTest, RemoveHigherPrecedenceOpFromStack)
{
    MockTokenizer tokenizer({
        {TokenType::Number  , 0, "1", 1},
        {TokenType::Asterisk, 2, "*", 0},
        {TokenType::Number  , 4, "2", 2},
        {TokenType::Plus    , 6, "+", 0},
        {TokenType::Number  , 8, "3", 3},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(3)(2)(1)*+", str.c_str());
}

TEST(ParserTest, DoNotRemoveLowerPrecedenceOpFromStack)
{
    MockTokenizer tokenizer({
        {TokenType::Number  , 0, "1", 1},
        {TokenType::Plus    , 2, "+", 0},
        {TokenType::Number  , 4, "2", 2},
        {TokenType::Asterisk, 6, "*", 0},
        {TokenType::Number  , 8, "3", 3},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(3)(2)*(1)+", str.c_str());
}

TEST(ParserTest, AdditionIsLeftAssociative)
{
    MockTokenizer tokenizer({
        {TokenType::Number, 0, "1", 1},
        {TokenType::Plus  , 2, "+", 0},
        {TokenType::Number, 4, "2", 2},
        {TokenType::Plus  , 6, "+", 0},
        {TokenType::Number, 8, "3", 3},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(3)(2)(1)++", str.c_str());
}

TEST(ParserTest, PowerIsRightAssociative)
{
    MockTokenizer tokenizer({
        {TokenType::Number, 0, "1", 1},
        {TokenType::Caret , 2, "^", 0},
        {TokenType::Number, 4, "2", 2},
        {TokenType::Caret , 6, "^", 0},
        {TokenType::Number, 8, "3", 3},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(3)(2)^(1)^", str.c_str());
}

TEST(ParserTest, UnaryOperators)
{
    MockTokenizer tokenizer({
        {TokenType::Plus    , 0, "+", 0},
        {TokenType::Number  , 2, "1", 1},
        {TokenType::Asterisk, 4, "*", 0},
        {TokenType::Minus   , 6, "-", 0},
        {TokenType::Number  , 8, "2", 2},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(-2)(+1)*", str.c_str());
}

TEST(ParserTest, SubExpression)
{
    MockTokenizer tokenizer({
        {TokenType::Number       ,  0, "1", 1},
        {TokenType::Asterisk     ,  2, "*", 0},
        {TokenType::OpeningParent,  4, ")", 0},
        {TokenType::Number       ,  6, "2", 2},
        {TokenType::Plus         ,  8, "+", 0},
        {TokenType::Number       , 10, "3", 3},
        {TokenType::ClosingParent, 12, "(", 0},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("((3)(2)+)(1)*", str.c_str());
}

TEST(ParserTest, Variable)
{
    MockTokenizer tokenizer({
        {TokenType::Identifier, 0, "foo", 0},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(foo())", str.c_str());
}

TEST(ParserTest, Function)
{
    MockTokenizer tokenizer({
        {TokenType::Identifier   ,  0, "foo", 0},
        {TokenType::OpeningParent,  2, ")"  , 0},
        {TokenType::Number       ,  4, "2"  , 2},
        {TokenType::Comma        ,  6, ","  , 0},
        {TokenType::Number       ,  8, "3"  , 3},
        {TokenType::ClosingParent, 10, "("  , 0},
    });

    Parser parser(&tokenizer);
    auto str = PrintST(parser.ParseInput());

    EXPECT_STREQ("(foo((3),(2)))", str.c_str());
}

// TODO: Add tests for errors, alternative function call syntax, etc.
