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


    using RuntimeException = Exception;

}

#endif // EXCEPTION_H
