#include "loggerservice.hpp"

namespace LoggerService
{
    Logger instance;

    ILoggerService exportService()
    {
        return ILoggerService(
                   LoggerService::trace,
                   LoggerService::debug,
                   LoggerService::info,
                   LoggerService::warn,
                   LoggerService::error,
                   LoggerService::critical
               );
    }

    Logger& getInstance()
    {
        return instance;
    }

    void setLogLevel(const ILoggerService::LogLevel level)
    {
        instance.setLogLevel(level);
    }

    void setLogFile(const std::filesystem::__cxx11::path filename)
    {
        instance.setLogFile(filename);
    }

    void trace(const char* const msg)
    {
        instance.trace(msg);
    }

    void debug(const char* const msg)
    {
        instance.debug(msg);
    }

    void info(const char* const msg)
    {
        instance.info(msg);
    }

    void warn(const char* const msg)
    {
        instance.warn(msg);
    }

    void error(const char* const msg)
    {
        instance.error(msg);
    }

    void critical(const char* const msg)
    {
        instance.critical(msg);
    }
}
