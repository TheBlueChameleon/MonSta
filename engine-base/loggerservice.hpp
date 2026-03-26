#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include <format>

struct ILoggerService;

namespace LoggerService
{
    void trace(const char* const msg);
    void debug(const char* const msg);
    void info(const char* const msg);
    void warn(const char* const msg);
    void error(const char* const msg);
    void critical(const char* const msg);

    template <typename... Args>
    void traceF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        trace(msg.c_str());
    }

    template <typename... Args>
    void debugF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        debug(msg.c_str());
    }

    template <typename... Args>
    void infoF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        info(msg.c_str());
    }

    template <typename... Args>
    void warnF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        warn(msg.c_str());
    }

    template <typename... Args>
    void errorF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        error(msg.c_str());
    }

    template <typename... Args>
    void criticalF(const std::format_string<Args...> fmt, Args&& ...args)
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        critical(msg.c_str());
    }
};

#endif // LOGGERSERVICE_HPP
