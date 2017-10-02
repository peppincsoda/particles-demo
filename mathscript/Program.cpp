#include "Program.h"
#include "Exception.h"

#include <climits>
#include <cassert>

using namespace std;

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

    RuntimeContext::RuntimeContext()
    {

    }

    FuncInterface* RuntimeContext::GetFunc(const std::string& name)
    {
        auto it = functions_.find(name);
        if (it == functions_.end())
            throw RuntimeException("Function not found");

        return it->second.get();
    }

    void RuntimeContext::AddFunc(const std::string& name, std::unique_ptr<FuncInterface>&& func)
    {
        functions_[name] = std::move(func);
    }

    void RuntimeContext::AddFunc(const std::string& name, const std::function<double ()>& func)
    {
        class Func : public FuncInterface
        {
        public:
            explicit Func(const std::function<double ()>& func) : func_(func) {}

            void Call(mathscript::RuntimeStack &stack) override
            {
                stack.Push(func_());
            }

        private:
            std::function<double ()> func_;
        };

        AddFunc(name, std::make_unique<Func>(func));
    }

    enum class OpCode
    {
        PushConst = 1,
        CallFunc,
    };

    Program::Program()
    {

    }

    double Program::Run(RuntimeContext& context) const
    {
        RuntimeStack stack;

        const char* ip = bytecode_.data();
        while (ip != bytecode_.data() + bytecode_.size()) {
            const auto opcode = static_cast<OpCode>(*ip);
            ip++;

            switch (opcode) {
            case OpCode::PushConst:
                stack.Push(ReadDouble(ip));
                break;

            case OpCode::CallFunc:
                context.GetFunc(ReadStr(ip))->Call(stack);
                break;

            default:
                throw RuntimeException("Invalid opcode");
            }
        }

        return stack.Pop();
    }

    void Program::EmitPushConst(double val)
    {
        bytecode_.push_back(static_cast<char>(OpCode::PushConst));
        bytecode_.insert(end(bytecode_), sizeof(double), 0);
        *reinterpret_cast<double*>(&bytecode_[bytecode_.size() - sizeof(double)]) = val;
    }

    void Program::EmitCallFunc(const std::string& name)
    {
        bytecode_.push_back(static_cast<char>(OpCode::CallFunc));
        const auto len = name.length();
        assert(len <= CHAR_MAX);
        bytecode_.push_back(len);
        bytecode_.insert(end(bytecode_), begin(name), end(name));
    }

    double Program::ReadDouble(const char*& ip)
    {
        auto val = *reinterpret_cast<const double*>(ip);
        ip += sizeof(double);
        return val;
    }

    string Program::ReadStr(const char*& ip)
    {
        const auto len = *ip;
        ip++;
        string s(ip, len);
        ip += len;
        return s;
    }
}
