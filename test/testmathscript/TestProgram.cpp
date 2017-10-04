
#include "gtest/gtest.h"

#include "mathscript/Program.h"

#include <memory>

using namespace mathscript;

TEST(ProgramTest, SingleConst)
{
    RuntimeContext context;

    Program program;
    program.EmitPushConst(42);

    const auto r = program.Run(context);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, SingleVariable)
{
    const double v = 42;

    RuntimeContext context;
    context.AddFunc("v", [&v]() { return v; });

    Program program;
    program.EmitCallFunc("v");

    const auto r = program.Run(context);
    ASSERT_EQ(42, r);
}

TEST(ProgramTest, SingleFunction)
{
    class TestFunc : public FuncInterface
    {
    public:
        void Call(RuntimeStack &stack) override
        {
            stack.Push(42);
        }
    };

    RuntimeContext context;
    context.AddFunc("test_func", std::make_unique<TestFunc>());

    Program program;
    program.EmitCallFunc("test_func");

    const auto r = program.Run(context);
    ASSERT_EQ(42, r);
}
