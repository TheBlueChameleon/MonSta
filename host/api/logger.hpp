#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <filesystem>

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

        const char* getPattern() const;
        void setPattern(const char* const pattern);

        std::optional<const char*> getLogFile() const;
        void setLogFile(const char* const filename);
        void unsetLogFile();

        void trace(const char* const msg) const;
        void debug(const char* const msg) const;
        void info(const char* const msg) const;
        void warn(const char* const msg) const;
        void error(const char* const msg) const;
        void critical(const char* const msg) const;

        // SpdLogger specifics
        void makeDefault() const;
        std::shared_ptr<spdlog::logger> expose();
};

constexpr auto DEFALUT_LOGGER_NAME = "MonStaLogger";
constexpr auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
constexpr auto DEFAULT_LOGGER_LEVEL = ILogger::LogLevel::TRACE;

#endif // LOGGER_HPP
