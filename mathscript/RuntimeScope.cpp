#include "RuntimeScope.h"

#include <cmath>

namespace mathscript {

    void RuntimeStack::Push(double val)
    {
        stack_.push(val);
    }

    double RuntimeStack::Pop()
    {
        const auto val = stack_.top();
        stack_.pop();
        return val;
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

        void Call(RuntimeStack& stack) override;

    private:
        std::function<_Fn> fn_;
    };

    template<>
    void FuncAdapter<double ()>::Call(RuntimeStack& stack)
    {
        stack.Push(fn_());
    }

    template<>
    void FuncAdapter<double (double)>::Call(RuntimeStack& stack)
    {
        const auto p1 = stack.Pop();
        stack.Push(fn_(p1));
    }

    template<>
    void FuncAdapter<double (double, double)>::Call(RuntimeStack& stack)
    {
        const auto p1 = stack.Pop();
        const auto p2 = stack.Pop();
        stack.Push(fn_(p1, p2));
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
