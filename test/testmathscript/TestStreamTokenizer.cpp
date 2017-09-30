
#include "gtest/gtest.h"

#include "mathscript/StreamTokenizer.h"

#include <sstream>

using namespace std;
using namespace mathscript;

TEST(StreamTokenizerTest, EndOfStream)
{
    std::istringstream ss("");

    StreamTokenizer input(ss);

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
}

TEST(StreamTokenizerTest, Operators)
{
    std::istringstream ss("  +  -  *  /  ^ ( ) , ");

    StreamTokenizer input(ss);

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::Plus);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Minus);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Asterisk);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Slash);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Caret);
    input >> t;
    EXPECT_EQ(t.type, TokenType::OpeningParent);
    input >> t;
    EXPECT_EQ(t.type, TokenType::ClosingParent);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Comma);
}

TEST(StreamTokenizerTest, Numbers)
{
    std::istringstream ss(" 12345  .345  12.  .  12.345");

    StreamTokenizer input(ss);

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, 12345);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, .345);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Invalid);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Invalid);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, 12.345);
}

TEST(StreamTokenizerTest, Identifiers)
{
    std::istringstream ss(" abcd_12 Abcd_12 _12 _ 12ab");

    StreamTokenizer input(ss);

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "abcd_12");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "Abcd_12");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "_12");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "_");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, 12);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "ab");
}
