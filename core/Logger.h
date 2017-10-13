#ifndef LOGGER_H
#define LOGGER_H

namespace core {

    enum class LogLevel
    {
        Error,
        Warning,
        Info,
        Debug,
    };

    class LoggerInterface
    {
    public:
        virtual ~LoggerInterface() {}
        virtual void WriteLog(LogLevel level, const char* file_name, int line, const char* format, ...) = 0;
    };

    LoggerInterface* GetLogger();
    void SetLogger(LoggerInterface* logger);
}

#define LOG_ERROR(...)   core::GetLogger()->WriteLog(core::LogLevel::Error  , __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) core::GetLogger()->WriteLog(core::LogLevel::Warning, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)    core::GetLogger()->WriteLog(core::LogLevel::Info   , __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...)   core::GetLogger()->WriteLog(core::LogLevel::Debug  , __FILE__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H
