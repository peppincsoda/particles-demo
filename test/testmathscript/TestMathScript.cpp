
#include "gtest/gtest.h"

#include "mathscript/MathScript.h"

using namespace mathscript;

TEST(MathScriptTest, SimpleConst)
{
    Program program(Compile("42"));
    const auto ret = mathscript::Run(program);
    EXPECT_EQ(42, ret);
}

TEST(MathScriptTest, SimpleFunc)
{
    Program program(Compile("foo"));
    RuntimeScope scope;
    scope.SetFunc("foo", []() { return 42; });
    const auto ret = program.Run(scope);
    EXPECT_EQ(42, ret);
}
