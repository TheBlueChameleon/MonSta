#include "logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger()
{
    auto consoleSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    consoleSink->set_level(static_cast<spdlog::level::level_enum>(DEFAULT_LOGGER_LEVEL));
    consoleSink->set_pattern(DEFAULT_LOGGER_PATTERN);

    logger = std::make_shared<spdlog::logger>(DEFALUT_LOGGER_NAME);
    logger->sinks().push_back(consoleSink);
    logger->set_level(static_cast<spdlog::level::level_enum>(DEFAULT_LOGGER_LEVEL));
}

ILogger::LogLevel Logger::getLogLevel() const
{
    return static_cast<ILogger::LogLevel>(logger->level());
}

void Logger::setLogLevel(const LogLevel level)
{
    logger->set_level(static_cast<spdlog::level::level_enum>(level));
    for (auto& sink : logger->sinks())
    {
        sink->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}

const std::string& Logger::getPattern() const
{
    return this->pattern;
}

void Logger::setPattern(const std::string_view& pattern)
{
    this->pattern = pattern;

    for (auto& sink : logger->sinks())
    {
        sink->set_pattern(pattern.data());
    }
}

std::optional<std::filesystem::__cxx11::path> Logger::getLogFile() const
{
    if (logfileSinkIndex == -1)
    {
        return std::nullopt;
    }
    else
    {
        return this->logfile;
    }
}

void Logger::setLogFile(const std::filesystem::path& filename)
{
    std::shared_ptr<spdlog::sinks::sink> fileSink;
    try
    {
        fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                       filename.c_str(),
                       /*truncate = */true
                   );
        fileSink->set_level(static_cast<spdlog::level::level_enum>(getLogLevel()));
        fileSink->set_pattern(getPattern());
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        ILogger::error("Could not set log file to '{}': {}", filename.c_str(), ex.what());
        return;
    }

    if (logfileSinkIndex == -1)
    {
        logfileSinkIndex = logger->sinks().size();
        logger->sinks().push_back(fileSink);
    }
    else
    {
        logger->sinks()[logfileSinkIndex] = fileSink;
    }
}

void Logger::unsetLogFile()
{
    if (logfileSinkIndex == -1)
    {
        logger->warn("Attempting to unset log file when none has been set.");
    }
    else
    {
        logger->sinks().erase(logger->sinks().begin() + logfileSinkIndex);
        logfile = "";
        logfileSinkIndex = -1;
    }
}

void Logger::trace(std::string_view msg) const
{
    logger->trace(msg);
}

void Logger::debug(std::string_view msg) const
{
    logger->debug(msg);
}

void Logger::info(std::string_view msg) const
{
    logger->info(msg);
}

void Logger::warn(std::string_view msg) const
{
    logger->warn(msg);
}

void Logger::error(std::string_view msg) const
{
    logger->error(msg);
}

void Logger::critical(std::string_view msg) const
{
    logger->critical(msg);
}

void Logger::makeDefault() const
{
    spdlog::set_default_logger(logger);
}

std::shared_ptr<spdlog::logger> Logger::expose()
{
    return logger;
}
