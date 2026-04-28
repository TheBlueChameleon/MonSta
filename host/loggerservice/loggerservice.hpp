#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include <filesystem>
#include <string_view>

#include <services/ILoggerService.hpp>

#include "logger.hpp"

namespace LoggerService
{
    ILoggerService exportService();

    Logger& getInstance();

    ILoggerService::LogLevel getLogLevelFromName(const std::string_view name);

    void setLogLevel(const ILoggerService::LogLevel level);
    void setLogFile(const std::filesystem::path filename);

    void trace(const std::string_view msg);
    void debug(const std::string_view msg);
    void info(const std::string_view msg);
    void warn(const std::string_view msg);
    void error(const std::string_view msg);
    void critical(const std::string_view msg);

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
