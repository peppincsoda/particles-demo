
#include "gtest/gtest.h"

#include "mathscript/StringTokenizer.h"

using namespace mathscript;

TEST(StringTokenizerTest, EndOfStream)
{
    StringTokenizer input("abcd");

    Token t;
    input >> t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
    EXPECT_STREQ(t.str_val.c_str(), "");
    input >> t;
    EXPECT_EQ(t.type, TokenType::EndOfStream);
    EXPECT_STREQ(t.str_val.c_str(), "");
}

TEST(StringTokenizerTest, Operators)
{
    StringTokenizer input("  +  -  *  /  ^ ( ) , ");

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::Plus);
    EXPECT_STREQ(t.str_val.c_str(), "+");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Minus);
    EXPECT_STREQ(t.str_val.c_str(), "-");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Asterisk);
    EXPECT_STREQ(t.str_val.c_str(), "*");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Slash);
    EXPECT_STREQ(t.str_val.c_str(), "/");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Caret);
    EXPECT_STREQ(t.str_val.c_str(), "^");
    input >> t;
    EXPECT_EQ(t.type, TokenType::OpeningParent);
    EXPECT_STREQ(t.str_val.c_str(), "(");
    input >> t;
    EXPECT_EQ(t.type, TokenType::ClosingParent);
    EXPECT_STREQ(t.str_val.c_str(), ")");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Comma);
    EXPECT_STREQ(t.str_val.c_str(), ",");
}

TEST(StringTokenizerTest, Numbers)
{
    StringTokenizer input(" 12345A  .345A  12.A  .  12.345");

    Token t;
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, 12345);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "A");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Number);
    EXPECT_EQ(t.dbl_val, .345);
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "A");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Invalid);
    EXPECT_STREQ(t.str_val.c_str(), "12.");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Identifier);
    EXPECT_STREQ(t.str_val.c_str(), "A");
    input >> t;
    EXPECT_EQ(t.type, TokenType::Invalid);
    EXPECT_STREQ(t.str_val.c_str(), ".");
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
