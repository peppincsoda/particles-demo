#include "MathScript.h"
#include "StringTokenizer.h"
#include "Parser.h"
#include "Generator.h"

namespace mathscript {

    Program Compile(const std::string& src)
    {
        StringTokenizer tokenizer(src);

        Parser parser(tokenizer);
        auto node = parser.ParseInput();

        Program program;
        GenerateCode(*node, program);

        return program;
    }

    double Run(const Program& program)
    {
        RuntimeScope scope;
        return program.Run(scope);
    }
}
