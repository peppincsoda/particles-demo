#include "Logger.h"

#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <iostream>
#include <memory>

namespace core {

    static const char* GetLogLevelStr(LogLevel level)
    {
        switch (level) {
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Info:    return "INFO";
        case LogLevel::Debug:   return "DEBUG";

        default:
            assert(0);
        }

        return "?";
    }

    class DefaultLogger : public LoggerInterface
    {
    public:
        virtual void WriteLog(LogLevel level, const char* file_name, int line, const char* format, ...)
        {
            va_list arg_list;
            va_start(arg_list, format);

            char message[1024];
            vsnprintf(message, sizeof(message), format, arg_list);

            char buffer[1024];
            snprintf(buffer, sizeof(buffer), "%s(%d): %s: %s", file_name, line, GetLogLevelStr(level), message);

            std::cout << buffer << std::endl;

            va_end(arg_list);
        }
    };

    static LoggerInterface* GetDefaultLogger()
    {
        static auto default_logger_ = std::make_unique<DefaultLogger>();
        return default_logger_.get();
    }

    static LoggerInterface* current_logger_ = GetDefaultLogger();

    LoggerInterface* GetLogger()
    {
        return current_logger_;
    }

    void SetLogger(LoggerInterface* logger)
    {
        current_logger_ = logger;
    }
}
