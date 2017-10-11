
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

TEST(MathScriptTest, ComplexExample)
{
    Program program(Compile("(100 - 1 + 9 * 3 ^ foo ^ .5) / 2 * 3"));
    RuntimeScope scope;
    scope.SetFunc("foo", []() { return 4; });
    const auto ret = program.Run(scope);
    EXPECT_EQ(270, ret);
}

TEST(MathScriptTest, HideFunction)
{
    auto program = Compile("min(1,2)");

    RuntimeScope scope;
    scope.SetFunc("min", nullptr);

    try {
        program.Run(scope);
        FAIL() << "Expected FunctionNotFoundException";
    } catch (FunctionNotFoundException& err) {
        EXPECT_STREQ(err.name().c_str(), "min");
    } catch (...) {
        FAIL() << "Expected FunctionNotFoundException";
    }
}
