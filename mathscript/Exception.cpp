#include "Exception.h"

#include <sstream>

namespace mathscript {

    const char* Exception::what() const noexcept
    {
        if (error_str_.empty()) {
            get_error_str(error_str_);
        }

        return error_str_.c_str();
    }

    ParserException::ParserException(int column, const std::string& token)
        : column_(column)
        , token_(token)
    {

    }

    ParserException::ParserException(int column, std::string&& token)
        : column_(column)
        , token_(std::move(token))
    {

    }

    int ParserException::column() const
    {
        return column_;
    }

    const std::string& ParserException::token() const
    {
        return token_;
    }

    ExpectedTokenException::ExpectedTokenException(int column, const std::string& token)
        : ParserException(column, token)
    {

    }

    ExpectedTokenException::ExpectedTokenException(int column, std::string&& token)
        : ParserException(column, std::move(token))
    {

    }

    void ExpectedTokenException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Expected token '" << token() << "' at column " << column();
        s = os.str();
    }

    UnexpectedTokenException::UnexpectedTokenException(int column, const std::string& token)
        : ParserException(column, token)
    {

    }

    UnexpectedTokenException::UnexpectedTokenException(int column, std::string&& token)
        : ParserException(column, std::move(token))
    {

    }

    void UnexpectedTokenException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Unexpected token '" << token() << "' at column " << column();
        s = os.str();
    }

    RuntimeException::RuntimeException(int ip)
        : ip_(ip)
    {

    }

    int RuntimeException::ip() const
    {
        return ip_;
    }

    FunctionNotFoundException::FunctionNotFoundException(int ip, const std::string& name)
        : RuntimeException(ip)
        , name_(name)
    {

    }

    FunctionNotFoundException::FunctionNotFoundException(int ip, std::string&& name)
        : RuntimeException(ip)
        , name_(std::move(name))
    {

    }

    const std::string& FunctionNotFoundException::name() const
    {
        return name_;
    }

    void FunctionNotFoundException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Function '" << name() << "' not found at ip " << ip();
        s = os.str();
    }

    FunctionBadNumOfParamsException::FunctionBadNumOfParamsException(int ip, const std::string& name)
        : FunctionNotFoundException(ip, name)
    {

    }

    FunctionBadNumOfParamsException::FunctionBadNumOfParamsException(int ip, std::string&& name)
        : FunctionNotFoundException(ip, std::move(name))
    {

    }

    void FunctionBadNumOfParamsException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Bad number of parameters for function '" << name() << "' at ip " << ip();
        s = os.str();
    }

    InvalidOpCodeException::InvalidOpCodeException(int ip)
        : RuntimeException(ip)
    {

    }

    void InvalidOpCodeException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Invalid opcode at ip " << ip();
        s = os.str();
    }

    StackUnderflowException::StackUnderflowException(int ip)
        : RuntimeException(ip)
    {

    }

    void StackUnderflowException::get_error_str(std::string& s) const
    {
        std::ostringstream os;
        os << "Stack underflow at ip " << ip();
        s = os.str();
    }

}
