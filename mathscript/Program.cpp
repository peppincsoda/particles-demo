#include "Program.h"
#include "Exception.h"

#include <cassert>

using namespace std;

namespace mathscript {

    enum class OpCode
    {
        PushConst = 1,
        CallFunc,
    };

    Program::Program()
    {

    }

    double Program::Run(RuntimeScope& scope) const
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

            case OpCode::CallFunc: {
                auto func = scope.GetFunc(ReadStr(ip));
                if (func == nullptr)
                    throw RuntimeException("Function not defined");
                func->Call(stack);
                break;
            }

            default:
                throw RuntimeException("Invalid opcode");
            }
        }

        return stack.Pop();
    }

    void Program::EmitPushConst(double val)
    {
        // NOTE: This is not endian-safe
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
        // NOTE: This is not endian-safe
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
