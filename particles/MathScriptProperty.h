#ifndef MATHSCRIPTPROPERTY_H
#define MATHSCRIPTPROPERTY_H

#include "Properties.h"

namespace particles {

    class MathScriptProgram;

    class MathScriptProperty : public PropertyInterface
    {
    public:
        MathScriptProperty(const std::string& name, MathScriptProgram& program);

        void Set(const std::string& str) override;
        std::string Get() const override;
        std::string Name() const override;

    private:
        std::string name_;
        MathScriptProgram& program_;
    };

}

#endif // MATHSCRIPTPROPERTY_H
