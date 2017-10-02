#ifndef PROGRAM_H
#define PROGRAM_H

#include <stack>
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include <vector>

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

    class RuntimeContext
    {
    public:
        RuntimeContext();

        RuntimeContext(const RuntimeContext&) = delete;
        RuntimeContext& operator=(const RuntimeContext&) = delete;

        FuncInterface* GetFunc(const std::string& name);

        void AddFunc(const std::string& name, std::unique_ptr<FuncInterface>&& func);
        void AddFunc(const std::string& name, const std::function<double ()>& func);

    private:
        std::unordered_map<std::string, std::unique_ptr<FuncInterface>> functions_;
    };

    class Program
    {
    public:
        Program();

        double Run(RuntimeContext& context) const;

        void EmitPushConst(double val);
        void EmitCallFunc(const std::string& name);

    private:
        static double ReadDouble(const char*& ip);
        static std::string ReadStr(const char*& ip);

        std::vector<char> bytecode_;
    };
}


#endif // PROGRAM_H
