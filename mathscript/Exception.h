#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace mathscript {

    class Exception : public std::exception
    {
    public:
        explicit Exception(const std::string& message);
        explicit Exception(std::string&& message);

        const char* what() const noexcept override;

        const std::string& message() const;

    private:
        std::string message_;
    };


    class ParserException : public Exception
    {
    public:
        ParserException(int column, const std::string& message);
        ParserException(int column, std::string&& message);

        int column() const;

    private:
        int column_;
    };


    using RuntimeException = Exception;
}

#endif // EXCEPTION_H
