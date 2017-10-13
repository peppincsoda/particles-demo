#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

namespace mathscript {

    using Exception = std::exception;

    /**
     * ParserException is thrown by the Parser on syntax errors.
     * Since MathScript expressions are single-line programs,
     * only a column index is needed to describe the position of the error.
     */
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

    //! A specific type of token was expected but wasn't found at the position.
    class ExpectedTokenException : public ParserException
    {
    public:
        ExpectedTokenException(int column, const std::string& token);
        ExpectedTokenException(int column, std::string&& token);
    };

    //! The type of token found is invalid at the position.
    class UnexpectedTokenException : public ParserException
    {
    public:
        UnexpectedTokenException(int column, const std::string& token);
        UnexpectedTokenException(int column, std::string&& token);
    };

    /**
     * RuntimeException is thrown by the Program on errors.
     * `ip` is the index of the instruction in the bytecode that caused the error.
     */
    class RuntimeException : public Exception
    {
    public:
        explicit RuntimeException(int ip);

        int ip() const;

    private:
        int ip_;
    };

    //! The function referred to by the code was not found in the runtime scope.
    class FunctionNotFoundException : public RuntimeException
    {
    public:
        FunctionNotFoundException(int ip, const std::string& name);
        FunctionNotFoundException(int ip, std::string&& name);

        const std::string& name() const;

    private:
        std::string name_;
    };

    //! The function referred to by the code and the corresponding
    //! function in the runtime scope have different number of parameters.
    class FunctionBadNumOfParamsException : public FunctionNotFoundException
    {
    public:
        FunctionBadNumOfParamsException(int ip, const std::string& name);
        FunctionBadNumOfParamsException(int ip, std::string&& name);
    };

    //! Invalid opcode was encountered.
    class InvalidOpCodeException : public RuntimeException
    {
    public:
        explicit InvalidOpCodeException(int ip);
    };

    //! Runtime stack underflow.
    class StackUnderflowException : public RuntimeException
    {
    public:
        explicit StackUnderflowException(int ip);
    };

}

#endif // EXCEPTION_H
