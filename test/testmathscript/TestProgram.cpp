
#include "gtest/gtest.h"

#include "mathscript/Program.h"
#include "mathscript/Exception.h"

#include <memory>

using namespace mathscript;

TEST(ProgramTest, SingleConst)
{
    RuntimeScope scope;

    Program p;
    p.EmitPushConst(42);

    const auto r = p.Run(scope);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, GenericFunction)
{
    class TestFunc : public FuncInterface
    {
    public:
        void Call(RuntimeContext &context) override
        {
            context.Push(42);
        }

        int GetNumParams() const
        {
            return 0;
        }
    };

    RuntimeScope scope;
    scope.SetFunc("test_func", std::make_unique<TestFunc>());

    Program p;
    p.EmitCallFunc("test_func", 0);

    const auto r = p.Run(scope);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, NativeVariable)
{
    const double v = 42;

    RuntimeScope scope;
    scope.SetFunc("v", [&v]() { return v; });

    Program p;
    p.EmitCallFunc("v", 0);

    const auto r = p.Run(scope);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, DefaultAddFunction)
{
    RuntimeScope scope;

    Program p;
    p.EmitPushConst(1);
    p.EmitPushConst(2);
    p.EmitCallFunc("__add__", 2);

    const auto r = p.Run(scope);
    ASSERT_EQ(3, r);
}

TEST(ProgramTest, FunctionNotFound)
{
    RuntimeScope scope;

    Program p;
    p.EmitCallFunc("f", 0);

    try {
        p.Run(scope);
        FAIL() << "Expected FunctionNotFoundException";
    } catch (FunctionNotFoundException& err) {
        EXPECT_STREQ(err.name().c_str(), "f");
        EXPECT_EQ(err.ip(), 0);
    } catch (...) {
        FAIL() << "Expected FunctionNotFoundException";
    }
}

TEST(ProgramTest, FunctionBadNumOfParams)
{
    RuntimeScope scope;
    scope.SetFunc("f", [](double p) { return p; });

    Program p;
    p.EmitCallFunc("f", 0);

    try {
        p.Run(scope);
        FAIL() << "Expected FunctionBadNumOfParamsException";
    } catch (FunctionBadNumOfParamsException& err) {
        EXPECT_STREQ(err.name().c_str(), "f");
        EXPECT_EQ(err.ip(), 0);
    } catch (...) {
        FAIL() << "Expected FunctionBadNumOfParamsException";
    }
}


