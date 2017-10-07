
#include "gtest/gtest.h"

#include "mathscript/Program.h"

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
        void Call(RuntimeStack &stack) override
        {
            stack.Push(42);
        }
    };

    RuntimeScope scope;
    scope.SetFunc("test_func", std::make_unique<TestFunc>());

    Program p;
    p.EmitCallFunc("test_func");

    const auto r = p.Run(scope);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, NativeVariable)
{
    const double v = 42;

    RuntimeScope scope;
    scope.SetFunc("v", [&v]() { return v; });

    Program p;
    p.EmitCallFunc("v");

    const auto r = p.Run(scope);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, DefaultAddFunction)
{
    RuntimeScope scope;

    Program p;
    p.EmitPushConst(1);
    p.EmitPushConst(2);
    p.EmitCallFunc("__add__");

    const auto r = p.Run(scope);
    ASSERT_EQ(3, r);
}
