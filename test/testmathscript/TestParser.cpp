
#include "gtest/gtest.h"

#include "mathscript/TokenizerInterface.h"
#include "mathscript/Parser.h"
#include "mathscript/STSerializer.h"
#include "mathscript/Exception.h"

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
        } else {
            token.type = TokenType::EndOfStream;
            if (tokens_.empty()) {
                token.column = 0;
            } else {
                const auto& last = *(it_ - 1);
                token.column = last.column + last.str_val.length();
            }
        }
    }

private:
    const std::vector<Token> tokens_;
    std::vector<Token>::const_iterator it_;
};

TEST(ParserTest, ReverseItems)
{
    MockTokenizer tokenizer({
        {TokenType::Number, 0, "1", 1},
        {TokenType::Plus  , 2, "+", 0},
        {TokenType::Number, 4, "2", 2},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

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

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

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

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

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

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("(3)(2)(1)++", str.c_str());
}

TEST(ParserTest, AdditionSubtractionSamePrecedence)
{
    MockTokenizer tokenizer({
        {TokenType::Number, 0, "1", 1},
        {TokenType::Minus , 2, "-", 0},
        {TokenType::Number, 4, "2", 2},
        {TokenType::Plus  , 6, "+", 0},
        {TokenType::Number, 8, "3", 3},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("(3)(2)(1)-+", str.c_str());
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

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

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

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("(2)-(1)+*", str.c_str());
}

TEST(ParserTest, SubExpression)
{
    MockTokenizer tokenizer({
        {TokenType::Number       ,  0, "1", 1},
        {TokenType::Asterisk     ,  2, "*", 0},
        {TokenType::OpeningParent,  4, "(", 0},
        {TokenType::Number       ,  6, "2", 2},
        {TokenType::Plus         ,  8, "+", 0},
        {TokenType::Number       , 10, "3", 3},
        {TokenType::ClosingParent, 12, ")", 0},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("(3)(2)+(1)*", str.c_str());
}

TEST(ParserTest, Variable)
{
    MockTokenizer tokenizer({
        {TokenType::Identifier, 0, "foo", 0},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("foo", str.c_str());
}

TEST(ParserTest, Function0Params)
{
    MockTokenizer tokenizer({
        {TokenType::Identifier   ,  0, "foo", 0},
        {TokenType::OpeningParent,  2, "("  , 0},
        {TokenType::ClosingParent, 10, ")"  , 0},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("foo", str.c_str());
}

TEST(ParserTest, Function2Params)
{
    MockTokenizer tokenizer({
        {TokenType::Identifier   ,  0, "foo", 0},
        {TokenType::OpeningParent,  2, "("  , 0},
        {TokenType::Number       ,  4, "2"  , 2},
        {TokenType::Comma        ,  6, ","  , 0},
        {TokenType::Number       ,  8, "3"  , 3},
        {TokenType::ClosingParent, 10, ")"  , 0},
    });

    Parser parser(tokenizer);
    auto str = SerializeST(*parser.ParseInput());

    EXPECT_STREQ("(3)(2)foo", str.c_str());
}

TEST(ParserErrorTest, UnexpectedToken)
{
    MockTokenizer tokenizer({
        {TokenType::Asterisk, 0, "*", 0},
    });

    try {
        Parser parser(tokenizer);
        parser.ParseInput();
        FAIL() << "Expected UnexpectedTokenException";
    } catch (UnexpectedTokenException& err) {
        EXPECT_EQ(err.column(), 0);
        EXPECT_STREQ(err.token().c_str(), "*");
    } catch (...) {
        FAIL() << "Expected UnexpectedTokenException";
    }
}

TEST(ParserErrorTest, ExpectedToken)
{
    MockTokenizer tokenizer({
        {TokenType::OpeningParent, 0, "(", 0},
        {TokenType::Number       , 1, "1", 1},
    });

    try {
        Parser parser(tokenizer);
        parser.ParseInput();
        FAIL() << "Expected ExpectedTokenException";
    } catch (ExpectedTokenException& err) {
        EXPECT_EQ(err.column(), 2);
        EXPECT_STREQ(err.token().c_str(), ")");
    } catch (...) {
        FAIL() << "Expected ExpectedTokenException";
    }
}

// TODO: Add more tests for errors
