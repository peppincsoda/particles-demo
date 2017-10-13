#include "Properties.h"

#include <sstream>

namespace particles {

    bool FromString(const std::string& str, bool& v)
    {
        if (str == "true")
            v = true;
        else if (str == "false")
            v = false;
        else
            return false;
        return true;
    }

    std::string ToString(bool v)
    {
        return v ? "true" : "false";
    }

    template<class T>
    bool FromString(const std::string& str, T& v)
    {
        std::istringstream is(str);
        is >> v;
        if (is.fail())
            return false;
        return true;
    }

    template<class T>
    std::string ToString(const T& val)
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }

    bool FromString(const std::string& str, int& v)
    {
        return FromString<int>(str, v);
    }

    std::string ToString(int v)
    {
        return ToString<int>(v);
    }

    bool FromString(const std::string& str, float& v)
    {
        return FromString<float>(str, v);
    }

    std::string ToString(float v)
    {
        return ToString<float>(v);
    }

    bool FromString(const std::string& str, std::string& v)
    {
        v = str;
        return true;
    }

    std::string ToString(const std::string& v)
    {
        return v;
    }

}
