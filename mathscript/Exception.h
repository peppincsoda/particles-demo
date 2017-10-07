#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace mathscript {

    class Exception : public std::exception
    {
    public:
        explicit Exception(const std::string& message)
            : message_(message)
        {
        }

        explicit Exception(std::string&& message)
            : message_(std::move(message))
        {

        }

        const char* what() const noexcept override
        {
            return message_.c_str();
        }

        const std::string& message() const
        {
            return message_;
        }

    private:
        std::string message_;
    };

    class ParserException : public Exception
    {
    public:
        ParserException(int column, const std::string& message)
            : Exception(message)
            , column_(column)
        {
        }

        explicit ParserException(int column, std::string&& message)
            : Exception(std::move(message))
            , column_(column)
        {

        }

        int column() const
        {
            return column_;
        }

    private:
        int column_;
    };



    using RuntimeException = Exception;



}

#endif // EXCEPTION_H
