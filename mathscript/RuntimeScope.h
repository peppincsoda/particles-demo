#ifndef RUNTIMESCOPE_H
#define RUNTIMESCOPE_H

#include <stack>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

namespace mathscript {

    class RuntimeStack
    {
    public:
        void Push(double val);
        double Pop();

    private:
        std::stack<double> stack_;
    };

    class FuncInterface
    {
    public:
        virtual ~FuncInterface() {}
        virtual void Call(RuntimeStack& stack) = 0;
    };

    class RuntimeScope
    {
    public:
        RuntimeScope();
        explicit RuntimeScope(RuntimeScope* parent);

        RuntimeScope(const RuntimeScope&) = delete;
        RuntimeScope& operator=(const RuntimeScope&) = delete;

        FuncInterface* GetFunc(const std::string& name);

        void SetFunc(const std::string& name, std::unique_ptr<FuncInterface>&& func);

        void SetFunc(const std::string& name, std::function<double ()>&& fn);
        void SetFunc(const std::string& name, std::function<double (double)>&& fn);
        void SetFunc(const std::string& name, std::function<double (double, double)>&& fn);

    private:
        RuntimeScope* parent_;

        std::unordered_map<std::string, std::unique_ptr<FuncInterface>> functions_;
    };

}

#endif // RUNTIMESCOPE_H
