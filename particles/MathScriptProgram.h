#ifndef MATHSCRIPTPROGRAM_H
#define MATHSCRIPTPROGRAM_H

#include "mathscript/Program.h"

namespace particles {

    class MathScriptProgram
    {
    public:
        MathScriptProgram(const std::string& src);

        MathScriptProgram(const MathScriptProgram&) = delete;
        MathScriptProgram& operator=(const MathScriptProgram&) = delete;

        void set_script(const std::string& src);
        std::string script() const;

        double Run(mathscript::RuntimeScope& scope) const;

    private:
        std::string script_;
        mathscript::Program program_;
    };
}

#endif // MATHSCRIPTPROGRAM_H
