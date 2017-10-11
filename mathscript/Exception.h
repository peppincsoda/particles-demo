#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace mathscript {

    using Exception = std::exception;

    class ParserException : public Exception
    {
    public:
        ParserException(int column, const std::string& token);
        ParserException(int column, std::string&& token);

        int column() const;
        const std::string& token() const;

    private:
        int column_;
        std::string token_;
    };

    class ExpectedTokenException : public ParserException
    {
    public:
        ExpectedTokenException(int column, const std::string& token);
        ExpectedTokenException(int column, std::string&& token);
    };

    class UnexpectedTokenException : public ParserException
    {
    public:
        UnexpectedTokenException(int column, const std::string& token);
        UnexpectedTokenException(int column, std::string&& token);
    };


    class RuntimeException : public Exception
    {
    public:
        explicit RuntimeException(int ip);

        int ip() const;

    private:
        int ip_;
    };

    class FunctionNotFoundException : public RuntimeException
    {
    public:
        FunctionNotFoundException(int ip, const std::string& name);
        FunctionNotFoundException(int ip, std::string&& name);

        const std::string& name() const;

    private:
        std::string name_;
    };

    class FunctionBadNumOfParamsException : public FunctionNotFoundException
    {
    public:
        FunctionBadNumOfParamsException(int ip, const std::string& name);
        FunctionBadNumOfParamsException(int ip, std::string&& name);
    };

    class InvalidOpCodeException : public RuntimeException
    {
    public:
        explicit InvalidOpCodeException(int ip);
    };

    class StackUnderflowException : public RuntimeException
    {
    public:
        explicit StackUnderflowException(int ip);
    };

}

#endif // EXCEPTION_H
