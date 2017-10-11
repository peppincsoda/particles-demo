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

    static double ReadDouble(const char*& ip);
    static string ReadStr(const char*& ip);

    Program::Program()
    {

    }

    double Program::Run(RuntimeScope& scope) const
    {
        RuntimeContext context;

        const char* ip = bytecode_.data();
        while (ip != bytecode_.data() + bytecode_.size()) {
            context.set_ip(ip - bytecode_.data());

            const auto opcode = static_cast<OpCode>(*ip);
            ip++;

            switch (opcode) {
            case OpCode::PushConst:
                context.Push(ReadDouble(ip));
                break;

            case OpCode::CallFunc: {
                const auto& name = ReadStr(ip);
                const auto num_params = *ip++;
                auto func = scope.GetFunc(name);
                if (func == nullptr)
                    throw FunctionNotFoundException(context.ip(), name);
                if (num_params != func->GetNumParams())
                    throw FunctionBadNumOfParamsException(context.ip(), name);
                func->Call(context);
                break;
            }

            default:
                throw InvalidOpCodeException(context.ip());
            }
        }

        return context.Pop();
    }

    void Program::EmitPushConst(double val)
    {
        // NOTE: This is not endian-safe
        bytecode_.push_back(static_cast<char>(OpCode::PushConst));
        bytecode_.insert(end(bytecode_), sizeof(double), 0);
        *reinterpret_cast<double*>(&bytecode_[bytecode_.size() - sizeof(double)]) = val;
    }

    void Program::EmitCallFunc(const std::string& name, int num_params)
    {
        bytecode_.push_back(static_cast<char>(OpCode::CallFunc));
        const auto len = name.length();
        assert(len <= CHAR_MAX);
        bytecode_.push_back(len);
        bytecode_.insert(end(bytecode_), begin(name), end(name));
        assert(num_params <= CHAR_MAX);
        bytecode_.push_back(num_params);
    }

    static double ReadDouble(const char*& ip)
    {
        // NOTE: This is not endian-safe
        auto val = *reinterpret_cast<const double*>(ip);
        ip += sizeof(double);
        return val;
    }

    static string ReadStr(const char*& ip)
    {
        const auto len = *ip;
        ip++;
        string s(ip, len);
        ip += len;
        return s;
    }
}
