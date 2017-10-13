#ifndef MATHSCRIPTPROPERTY_H
#define MATHSCRIPTPROPERTY_H

#include "Properties.h"

namespace particles {

    //! MathScriptProperty allows only valid MathScript expressions to be set into a string variable
    class MathScriptProperty : public PropertyInterface
    {
    public:
        MathScriptProperty(const std::string& name, std::string& value);

        bool Set(const std::string& str) override;
        std::string Get() const override;
        std::string Name() const override;

    private:
        std::string name_;
        std::string& value_;
    };

}

#endif // MATHSCRIPTPROPERTY_H
