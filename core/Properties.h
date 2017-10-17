#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
#include <vector>
#include <memory>


namespace core {

    bool FromString(const std::string& str, bool& v);
    std::string ToString(bool v);

    bool FromString(const std::string& str, int& v);
    std::string ToString(int v);

    bool FromString(const std::string& str, float& v);
    std::string ToString(float v);

    bool FromString(const std::string& str, std::string& v);
    std::string ToString(const std::string& v);

    enum class PropertyType
    {
        Invalid,
        Boolean,
        Integer,
        Double,
        Script,
        ImagePath,
    };

    template<class _T>
    struct DefaultType
    {
    };

    template<> struct DefaultType<bool>
    {
        static const auto value = PropertyType::Boolean;
    };

    template<>
    struct DefaultType<int>
    {
        static const auto value = PropertyType::Integer;
    };

    template<>
    struct DefaultType<float>
    {
        static const auto value = PropertyType::Double;
    };

    template<>
    struct DefaultType<double>
    {
        static const auto value = PropertyType::Double;
    };


    class PropertyInterface
    {
    public:
        virtual ~PropertyInterface() {}
        virtual bool Set(const std::string& str) = 0;
        virtual std::string Get() const = 0;
        virtual std::string Name() const = 0;
        virtual PropertyType Type() const = 0;
    };


    class HasProperties
    {
    public:
        virtual ~HasProperties() {}
        virtual std::vector<std::unique_ptr<PropertyInterface>> Properties() = 0;
    };


    template<class _T, PropertyType _Type = DefaultType<_T>::value>
    class Property : public PropertyInterface
    {
    public:
        Property(const std::string& name, _T& value)
            : name_(name)
            , value_(value)
        {

        }

        bool Set(const std::string& str) override
        {
            return FromString(str, value_);
        }

        std::string Get() const override
        {
            return ToString(value_);
        }

        std::string Name() const override
        {
            return name_;
        }

        PropertyType Type() const override
        {
            return _Type;
        }

    private:
        std::string name_;
        _T& value_;
    };

}


#endif // PROPERTIES_H
