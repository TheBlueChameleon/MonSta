#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include <format>
#include <string_view>

struct ILoggerService;

namespace LoggerService
{
    void trace(const std::string_view msg);
    void debug(const std::string_view msg);
    void info(const std::string_view msg);
    void warn(const std::string_view msg);
    void error(const std::string_view msg);
    void critical(const std::string_view msg);

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
