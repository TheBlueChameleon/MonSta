#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include <format>

struct ILoggerService;

struct LoggerService
{
    static void trace(const char* const msg);
    static void debug(const char* const msg);
    static void info(const char* const msg);
    static void warn(const char* const msg);
    static void error(const char* const msg);
    static void critical(const char* const msg);

    template <typename... Args>
    static void traceF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        trace(msg.c_str());
    }

    template <typename... Args>
    static void debugF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        debug(msg.c_str());
    }

    template <typename... Args>
    static void infoF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        info(msg.c_str());
    }

    template <typename... Args>
    static void warnF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        warn(msg.c_str());
    }

    template <typename... Args>
    static void errorF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        error(msg.c_str());
    }

    template <typename... Args>
    static void criticalF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        critical(msg.c_str());
    }
};

#endif // LOGGERSERVICE_HPP
