#include "MathScriptProperty.h"
#include "ScriptScope.h"

#include "mathscript/MathScript.h"
#include "core/Logger.h"

namespace particles {

    MathScriptProperty::MathScriptProperty(const std::string& name, std::string& value)
        : name_(name)
        , value_(value)
    {

    }

    bool MathScriptProperty::Set(const std::string& str)
    {
        try {
            auto p = mathscript::Compile(str);

            // Run the program using our scope to check if it
            // contains undefined identifiers
            ScriptScope scope;
            p.Run(scope);
        } catch (mathscript::Exception& e) {
            LOG_WARNING("Compilation of property '%s' failed: %s", name_.c_str(), e.what());
            return false;
        }

        value_ = str;
        return true;
    }

    std::string MathScriptProperty::Get() const
    {
        return value_;
    }

    std::string MathScriptProperty::Name() const
    {
        return name_;
    }

}
