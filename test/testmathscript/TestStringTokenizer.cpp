
#include "gtest/gtest.h"

#include "mathscript/StringTokenizer.h"

using namespace mathscript;

TEST(StringTokenizerTest, EndOfStream)
{
    StringTokenizer input("");

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
}

TEST(StringTokenizerTest, Operators)
{
    StringTokenizer input("  +  -  *  /  ^ ( ) , ");

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

TEST(StringTokenizerTest, Numbers)
{
    StringTokenizer input(" 12345  .345  12.  .  12.345");

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

TEST(StringTokenizerTest, Identifiers)
{
    StringTokenizer input(" abcd_12 Abcd_12 _12 _ 12ab");

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
