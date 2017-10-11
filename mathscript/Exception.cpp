#include "Exception.h"

namespace mathscript {

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

    UnexpectedTokenException::UnexpectedTokenException(int column, const std::string& token)
        : ParserException(column, token)
    {

    }

    UnexpectedTokenException::UnexpectedTokenException(int column, std::string&& token)
        : ParserException(column, std::move(token))
    {

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

    FunctionBadNumOfParamsException::FunctionBadNumOfParamsException(int ip, const std::string& name)
        : FunctionNotFoundException(ip, name)
    {

    }

    FunctionBadNumOfParamsException::FunctionBadNumOfParamsException(int ip, std::string&& name)
        : FunctionNotFoundException(ip, std::move(name))
    {

    }

    const std::string& FunctionNotFoundException::name() const
    {
        return name_;
    }

    InvalidOpCodeException::InvalidOpCodeException(int ip)
        : RuntimeException(ip)
    {

    }

    StackUnderflowException::StackUnderflowException(int ip)
        : RuntimeException(ip)
    {

    }
}
