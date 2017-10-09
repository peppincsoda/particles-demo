#include "Properties.h"

#include "mathscript/Exception.h"

#include <sstream>

namespace particles {

    bool FromString(const std::string& str, bool)
    {
        if (str == "true")
            return true;
        else if (str == "false")
            return false;

        throw mathscript::Exception("Cannot convert value to boolean");
    }

    std::string ToString(bool v)
    {
        return v ? "true" : "false";
    }

    template<class T>
    T FromString(const std::string& str)
    {
        std::istringstream is(str);
        T val;
        is >> val;
        if (is.fail())
            throw mathscript::Exception("Cannot convert value");
        return val;
    }

    template<class T>
    std::string ToString(const T& val)
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }

    int FromString(const std::string& str, int)
    {
        return FromString<int>(str);
    }

    std::string ToString(int v)
    {
        return ToString<int>(v);
    }

    float FromString(const std::string& str, float)
    {
        return FromString<float>(str);
    }

    std::string ToString(float v)
    {
        return ToString<float>(v);
    }

    std::string FromString(const std::string& str, std::string)
    {
        return str;
    }

    std::string ToString(const std::string& v)
    {
        return v;
    }

}
