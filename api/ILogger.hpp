#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

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

    virtual const std::string& getPattern() const = 0;
    virtual void setPattern(const std::string_view& pattern) = 0;

    virtual std::optional<std::filesystem::path> getLogFile() const = 0;
    virtual void setLogFile(const std::filesystem::path& filename) = 0;
    virtual void unsetLogFile() = 0;

    virtual void trace(std::string_view msg) const = 0;
    virtual void debug(std::string_view msg) const = 0;
    virtual void info(std::string_view msg) const = 0;
    virtual void warn(std::string_view msg) const = 0;
    virtual void error(std::string_view msg) const = 0;
    virtual void critical(std::string_view msg) const = 0;

    template <typename... Args>
    void trace(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->trace(msg);
    }

    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->debug(msg);
    }

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->info(msg);
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->warn(msg);
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->error(msg);
    }

    template <typename... Args>
    void critical(std::format_string<Args...> fmt, Args&& ...args) const
    {
        const auto msg = std::format(fmt, std::forward<Args>(args)...);
        this->critical(msg);
    }
};

constexpr auto DEFAULT_LOGGER_FILE = "MonSta.log";
constexpr auto DEFALUT_LOGGER_NAME = "MonStaLogger";
constexpr auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
constexpr auto DEFAULT_LOGGER_LEVEL = ILogger::LogLevel::TRACE;

#endif // ILOGGER_HPP
