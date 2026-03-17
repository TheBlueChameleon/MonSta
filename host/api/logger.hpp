#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <filesystem>
#include <string>

#include <spdlog/spdlog.h>

#include <ILogger.hpp>

class Logger : public virtual ILogger
{
    private:
        std::shared_ptr<spdlog::logger> logger;
        std::string pattern;
        std::filesystem::path logfile;
        int logfileSinkIndex = -1;

    public:
        Logger();

        // ILogger interface
        LogLevel getLogLevel() const;
        void setLogLevel(const LogLevel level);

        const std::string& getPattern() const;
        void setPattern(const std::string_view& pattern);

        std::optional<std::filesystem::path> getLogFile() const;
        void setLogFile(const std::filesystem::path& filename);
        void unsetLogFile();

        void trace(std::string_view msg) const;
        void debug(std::string_view msg) const;
        void info(std::string_view msg) const;
        void warn(std::string_view msg) const;
        void error(std::string_view msg) const;
        void critical(std::string_view msg) const;

        // SpdLogger specifics
        void makeDefault() const;
        std::shared_ptr<spdlog::logger> expose();
};

constexpr auto DEFALUT_LOGGER_NAME = "MonStaLogger";
constexpr auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
constexpr auto DEFAULT_LOGGER_LEVEL = ILogger::LogLevel::TRACE;

#endif // LOGGER_HPP
