#ifndef COMPILER_H
#define COMPILER_H

#include "Program.h"
#include "Exception.h"

namespace mathscript {

    //! Compile MathScript source into a program.
    Program Compile(const std::string& src);

    //! Run MathScript program and return its result.
    double Run(const Program& program);
}

#endif // COMPILER_H
