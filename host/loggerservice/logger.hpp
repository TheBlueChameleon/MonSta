#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <filesystem>
#include <format>
#include <optional>

#include <services/ILoggerService.hpp>

namespace spdlog
{
    class logger;
    namespace sinks
    {
        class sink;
    }
}

class Logger
{
    private:
        std::shared_ptr<spdlog::logger>         logger;
        std::string                             pattern;
        std::optional<std::filesystem::path>    logfile;

    public:
        Logger();

        ILoggerService::LogLevel getLogLevel() const;
        void setLogLevel(const ILoggerService::LogLevel level);

        std::string getPattern() const;
        void setPattern(const std::string_view pattern);

        std::optional<std::filesystem::path> getLogFile() const;
        void setLogFile(const std::filesystem::path filename);
        void unsetLogFile();

        void makeDefault() const;

        std::shared_ptr<spdlog::logger>      expose();
        std::shared_ptr<spdlog::sinks::sink> getConsSink() const;
        std::shared_ptr<spdlog::sinks::sink> getFileSink() const;

        void trace(const std::string_view msg) const;
        void debug(const std::string_view msg) const;
        void info(const std::string_view msg) const;
        void warn(const std::string_view msg) const;
        void error(const std::string_view msg) const;
        void critical(const std::string_view msg) const;

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

#endif // LOGGER_HPP
