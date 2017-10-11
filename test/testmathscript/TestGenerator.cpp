
#include "gtest/gtest.h"

#include "mathscript/Parser.h"
#include "mathscript/Generator.h"

#include <memory>

using namespace mathscript;

TEST(GeneratorTest, SingleConst)
{
    auto num = std::make_unique<STNum>();
    num->dbl_val_ = 42;

    Program program;
    GenerateCode(*num, program);

    RuntimeScope scope;
    const auto ret = program.Run(scope);
    EXPECT_EQ(42, ret);
}

TEST(GeneratorTest, GenericFunction)
{
    // test_func(42)
    auto func = std::make_unique<STFunc>();
    func->name_ = "test_func";
    {
        auto num = std::make_unique<STNum>();
        num->dbl_val_ = 42;
        func->params_.push_back(std::move(num));
    }

    Program p;
    GenerateCode(*func, p);


    // double test_func(double d) { return d + 1; }
    class Increment : public FuncInterface
    {
    public:
        void Call(RuntimeContext &context) override
        {
            context.Push(context.Pop() + 1);
        }

        int GetNumParams() const
        {
            return 1;
        }
    };

    RuntimeScope scope;
    scope.SetFunc("test_func", std::make_unique<Increment>());

    const auto r = p.Run(scope);
    ASSERT_EQ(43, r);
}

TEST(GeneratorTest, DefaultAddFunction)
{
    // 1 + 2
    auto expr = std::make_unique<STExpr>();
    {
        auto num = std::make_unique<STNum>();
        num->dbl_val_ = 2;
        expr->AddTerm(std::move(num));
    }
    {
        auto num = std::make_unique<STNum>();
        num->dbl_val_ = 1;
        expr->AddTerm(std::move(num));
    }
    expr->AddOp(TokenType::Plus);

    Program p;
    GenerateCode(*expr, p);

    RuntimeScope scope;
    const auto r = p.Run(scope);
    ASSERT_EQ(3, r);
}
