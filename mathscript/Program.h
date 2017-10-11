#ifndef PROGRAM_H
#define PROGRAM_H

#include "RuntimeScope.h"

#include <vector>

namespace mathscript {

    class Program
    {
    public:
        Program();

        Program(const Program&) = default;
        Program& operator=(const Program&) = default;

        Program(Program&&) = default;
        Program& operator=(Program&&) = default;

        double Run(RuntimeScope& scope) const;

        void EmitPushConst(double val);
        void EmitCallFunc(const std::string& name, int num_params);

    private:
        std::vector<char> bytecode_;
    };
}


#endif // PROGRAM_H
