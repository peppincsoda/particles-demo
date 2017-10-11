#include "RuntimeScope.h"
#include "Exception.h"

#include <cmath>

namespace mathscript {

    RuntimeContext::RuntimeContext()
        : stack_()
        , ip_(0)
    {

    }

    RuntimeContext::~RuntimeContext()
    {

    }

    void RuntimeContext::Push(double val)
    {
        stack_.push(val);
    }

    double RuntimeContext::Pop()
    {
        if (stack_.empty())
            throw StackUnderflowException(ip_);

        const auto val = stack_.top();
        stack_.pop();
        return val;
    }

    int RuntimeContext::ip() const
    {
        return ip_;
    }

    void RuntimeContext::set_ip(int ip)
    {
        ip_ = ip;
    }


    static RuntimeScope* DefaultRuntimeScope()
    {
        static std::unique_ptr<RuntimeScope> default_;
        if (default_ == nullptr) {
            default_ = std::make_unique<RuntimeScope>(nullptr);
            default_->SetFunc("__add__", [](double x, double y) { return x + y; });
            default_->SetFunc("__sub__", [](double x, double y) { return x - y; });
            default_->SetFunc("__mul__", [](double x, double y) { return x * y; });
            default_->SetFunc("__div__", [](double x, double y) { return x / y; });
            default_->SetFunc("__pow__", [](double x, double y) { return std::pow(x, y); });

            default_->SetFunc("__pos__", [](double x) { return x; });
            default_->SetFunc("__neg__", [](double x) { return -x; });

            default_->SetFunc("min", [](double x, double y) { return std::min(x, y); });
            default_->SetFunc("max", [](double x, double y) { return std::max(x, y); });

            default_->SetFunc("abs", [](double x) { return std::abs(x); });
            default_->SetFunc("sin", [](double x) { return std::sin(x); });
            default_->SetFunc("cos", [](double x) { return std::cos(x); });
            default_->SetFunc("sqr", [](double x) { return x * x; });
            default_->SetFunc("sqrt", [](double x) { return std::sqrt(x); });
        }

        return default_.get();
    }

    RuntimeScope::RuntimeScope()
        : parent_(DefaultRuntimeScope())
    {

    }

    RuntimeScope::RuntimeScope(RuntimeScope* parent)
        : parent_(parent)
    {
    }

    FuncInterface* RuntimeScope::GetFunc(const std::string& name)
    {
        const auto it = functions_.find(name);
        if (it != functions_.end())
            return it->second.get();
        else if (parent_ != nullptr)
            return parent_->GetFunc(name);
        return nullptr;
    }

    void RuntimeScope::SetFunc(const std::string& name, std::unique_ptr<FuncInterface>&& func)
    {
        functions_[name] = std::move(func);
    }

    template<typename _Fn>
    class FuncAdapter : public FuncInterface
    {
    public:
        explicit FuncAdapter(std::function<_Fn>&& fn)
            : fn_(std::move(fn))
        {

        }

        void Call(RuntimeContext& context) override;
        int GetNumParams() const override;

    private:
        std::function<_Fn> fn_;
    };

    template<>
    void FuncAdapter<double ()>::Call(RuntimeContext& context)
    {
        context.Push(fn_());
    }

    template<>
    void FuncAdapter<double (double)>::Call(RuntimeContext& context)
    {
        const auto p1 = context.Pop();
        context.Push(fn_(p1));
    }

    template<>
    void FuncAdapter<double (double, double)>::Call(RuntimeContext& context)
    {
        const auto p1 = context.Pop();
        const auto p2 = context.Pop();
        context.Push(fn_(p1, p2));
    }

    template<>
    int FuncAdapter<double ()>::GetNumParams() const
    {
        return 0;
    }

    template<>
    int FuncAdapter<double (double)>::GetNumParams() const
    {
        return 1;
    }

    template<>
    int FuncAdapter<double (double, double)>::GetNumParams() const
    {
        return 2;
    }

    void RuntimeScope::SetFunc(const std::string& name, std::function<double ()>&& fn)
    {
        SetFunc(name, std::make_unique<FuncAdapter<double ()>>(std::move(fn)));
    }

    void RuntimeScope::SetFunc(const std::string& name, std::function<double (double)>&& fn)
    {
        SetFunc(name, std::make_unique<FuncAdapter<double (double)>>(std::move(fn)));
    }

    void RuntimeScope::SetFunc(const std::string& name, std::function<double (double, double)>&& fn)
    {
        SetFunc(name, std::make_unique<FuncAdapter<double (double, double)>>(std::move(fn)));
    }

}
