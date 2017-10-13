#ifndef GENERATOR_H
#define GENERATOR_H

#include "STNode.h"
#include "Program.h"

namespace mathscript {

    //! Emit code into `program` while traversing the AST given by `node`.
    void GenerateCode(STNode& node, Program& program);

}

#endif // GENERATOR_H
