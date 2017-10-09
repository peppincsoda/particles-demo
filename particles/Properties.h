#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <vector>
#include <memory>


namespace particles {

    bool FromString(const std::string& str, bool);
    std::string ToString(bool v);

    int FromString(const std::string& str, int);
    std::string ToString(int v);

    float FromString(const std::string& str, float);
    std::string ToString(float v);

    std::string FromString(const std::string& str, std::string);
    std::string ToString(const std::string& v);


    class PropertyInterface
    {
    public:
        virtual ~PropertyInterface() {}
        virtual void Set(const std::string& str) = 0;
        virtual std::string Get() const = 0;
        virtual std::string Name() const = 0;
    };


    class HasProperties
    {
    public:
        virtual ~HasProperties() {}
        virtual std::vector<std::unique_ptr<PropertyInterface>> Properties() = 0;
    };


    template<class _T>
    class Property : public PropertyInterface
    {
    public:
        Property(const std::string& name, _T& value)
            : name_(name)
            , value_(value)
        {

        }

        void Set(const std::string& str) override
        {
            value_ = FromString(str, _T());
        }

        std::string Get() const override
        {
            return ToString(value_);
        }

        std::string Name() const override
        {
            return name_;
        }

    private:
        std::string name_;
        _T& value_;
    };


    template<class _C, class _T>
    class GetterSetterProperty : public PropertyInterface
    {
    public:
        GetterSetterProperty(const std::string& name,
                             _T (_C::*getter)() const,
                             void (_C::*setter)(_T),
                             _C& instance)
            : name_(name)
            , getter_(getter)
            , setter_(setter)
            , instance_(instance)
        {
        }

        void Set(const std::string& str) override
        {
            (setter_.*instance_)(FromString(str, _T()));
        }

        std::string Get() const override
        {
            return ToString((getter_.*instance_)());
        }

        std::string Name() const override
        {
            return name_;
        }

    private:
        std::string name_;
        _T   (_C::*getter_)() const;
        void (_C::*setter_)(_T);
        _C& instance_;
    };

}


#endif // PROPERTIES_H
