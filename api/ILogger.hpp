#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <format>
#include <optional>

struct ILogger
{
    enum class LogLevel : int
    {
        TRACE    = 0,
        DEBUG    = 1,
        INFO     = 2,
        WARN     = 3,
        ERROR    = 4,
        CRITICAL = 5,
        OFF      = 6,
        N_LEVELS
    };


    virtual ~ILogger() = default;

    virtual LogLevel getLogLevel() const = 0;
    virtual void setLogLevel(const LogLevel level) = 0;

    virtual const char* getPattern() const = 0;
    virtual void setPattern(const char* const pattern) = 0;

    virtual std::optional<const char*> getLogFile() const = 0;
    virtual void setLogFile(const char* const filename) = 0;
    virtual void unsetLogFile() = 0;

    virtual void trace(const char* const msg) const = 0;
    virtual void debug(const char* const msg) const = 0;
    virtual void info(const char* const msg) const = 0;
    virtual void warn(const char* const msg) const = 0;
    virtual void error(const char* const msg) const = 0;
    virtual void critical(const char* const msg) const = 0;

    template <typename... Args>
    void trace(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->trace(msg.c_str());
    }

    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->debug(msg.c_str());
    }

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->info(msg.c_str());
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->warn(msg.c_str());
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->error(msg.c_str());
    }

    template <typename... Args>
    void critical(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->critical(msg.c_str());
    }
};

#endif // ILOGGER_HPP
