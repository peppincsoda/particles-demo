#include "MathScriptProperty.h"
#include "MathScriptProgram.h"

namespace particles {

    MathScriptProperty::MathScriptProperty(const std::string& name, MathScriptProgram& program)
        : name_(name)
        , program_(program)
    {

    }

    void MathScriptProperty::Set(const std::string& str)
    {
        program_.set_script(str);
    }

    std::string MathScriptProperty::Get() const
    {
        return program_.script();
    }

    std::string MathScriptProperty::Name() const
    {
        return name_;
    }

}
