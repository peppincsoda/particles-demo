#ifndef PROGRAM_H
#define PROGRAM_H

#include "RuntimeScope.h"

#include <vector>

namespace mathscript {

    class Program
    {
    public:
        Program();

        Program(const Program&);
        Program& operator=(const Program&) = delete;

        Program(Program&&);
        Program& operator=(Program&&) = delete;

        double Run(RuntimeScope& scope) const;

        void EmitPushConst(double val);
        void EmitCallFunc(const std::string& name);

    private:
        static double ReadDouble(const char*& ip);
        static std::string ReadStr(const char*& ip);

        std::vector<char> bytecode_;
    };
}


#endif // PROGRAM_H
