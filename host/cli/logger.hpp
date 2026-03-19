#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <filesystem>
#include <format>

#include <ILoggerService.hpp>

namespace spdlog
{
    class logger;
}

class Logger
{
    private:
        std::shared_ptr<spdlog::logger> logger;
        std::string pattern;
        std::filesystem::path logfile;
        int logfileSinkIndex = -1;

    public:
        Logger();

        ILoggerService::LogLevel getLogLevel() const;
        void setLogLevel(const ILoggerService::LogLevel level);

        const char* getPattern() const;
        void setPattern(const char* const pattern);

        std::optional<const char*> getLogFile() const;
        void setLogFile(const char* const filename);
        void unsetLogFile();

        void makeDefault() const;
        std::shared_ptr<spdlog::logger> expose();

        void trace(const char* const msg) const;
        void debug(const char* const msg) const;
        void info(const char* const msg) const;
        void warn(const char* const msg) const;
        void error(const char* const msg) const;
        void critical(const char* const msg) const;

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

constexpr auto DEFALUT_LOGGER_NAME = "MonStaLogger";
constexpr auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
constexpr auto DEFAULT_LOGGER_LEVEL = ILoggerService::LogLevel::TRACE;

#endif // LOGGER_HPP
