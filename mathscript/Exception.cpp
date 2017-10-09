#include "Exception.h"

namespace mathscript {

    Exception::Exception(const std::string& message)
        : message_(message)
    {
    }

    Exception::Exception(std::string&& message)
        : message_(std::move(message))
    {

    }

    const char* Exception::what() const noexcept
    {
        return message_.c_str();
    }

    const std::string& Exception::message() const
    {
        return message_;
    }


    ParserException::ParserException(int column, const std::string& message)
        : Exception(message)
        , column_(column)
    {
    }

    ParserException::ParserException(int column, std::string&& message)
        : Exception(std::move(message))
        , column_(column)
    {

    }

    int ParserException::column() const
    {
        return column_;
    }

}
