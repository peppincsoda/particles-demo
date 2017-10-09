#include "MathScriptProgram.h"
#include "ScriptScope.h"

#include "mathscript/MathScript.h"

namespace particles {

    MathScriptProgram::MathScriptProgram(const std::string& src)
    {
        set_script(src);
    }

    void MathScriptProgram::set_script(const std::string& src)
    {
        auto program = mathscript::Compile(src);

        // By running the program we can check that it
        // doesn't contain any references our scope doesn't know about
        ScriptScope scope;
        program.Run(scope);

        program_ = std::move(program);
        script_ = src;
    }

    std::string MathScriptProgram::script() const
    {
        return script_;
    }

    double MathScriptProgram::Run(mathscript::RuntimeScope& scope) const
    {
        return program_.Run(scope);
    }

}
