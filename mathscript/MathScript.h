#ifndef COMPILER_H
#define COMPILER_H

#include "Program.h"

namespace mathscript {

    Program Compile(const std::string& src);

    double Run(const Program& program);
}

#endif // COMPILER_H
