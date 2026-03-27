#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include "logging/logger.hpp"

struct LoggingDefinition;

namespace LoggerService
{
    Logger& getInstance();

    void setLogLevel(const ILoggerService::LogLevel level);
    void setup(const LoggingDefinition def);

    void trace(const char* const msg);
    void debug(const char* const msg);
    void info(const char* const msg);
    void warn(const char* const msg);
    void error(const char* const msg);
    void critical(const char* const msg);

    template <typename... Args>
    void traceF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::trace(msg.c_str());
    }

    template <typename... Args>
    void debugF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::debug(msg.c_str());
    }

    template <typename... Args>
    void infoF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::info(msg.c_str());
    }

    template <typename... Args>
    void warnF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::warn(msg.c_str());
    }

    template <typename... Args>
    void errorF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::error(msg.c_str());
    }

    template <typename... Args>
    void criticalF(std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        LoggerService::critical(msg.c_str());
    }
}

#endif // LOGGERSERVICE_HPP
