#include <spdlog/spdlog.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "logger.hpp"

Logger::Logger()
{
    auto consSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    consSink->set_level(static_cast<spdlog::level::level_enum>(DEFAULT_LOGGER_LEVEL));
    consSink->set_pattern(DEFAULT_LOGGER_PATTERN);

    logger = std::make_shared<spdlog::logger>(DEFAULT_LOGGER_NAME);
    logger->sinks().push_back(consSink);
    logger->set_level(static_cast<spdlog::level::level_enum>(DEFAULT_LOGGER_LEVEL));
}

ILoggerService::LogLevel Logger::getLogLevel() const
{
    return static_cast<ILoggerService::LogLevel>(logger->level());
}

void Logger::setLogLevel(const ILoggerService::LogLevel level)
{
    logger->set_level(static_cast<spdlog::level::level_enum>(level));
    for (auto& sink : logger->sinks())
    {
        sink->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}

std::string Logger::getPattern() const
{
    return this->pattern;
}

void Logger::setPattern(const std::string_view pattern)
{
    this->pattern = pattern;

    for (auto& sink : logger->sinks())
    {
        sink->set_pattern(pattern.data());
    }
}

std::optional<std::filesystem::path> Logger::getLogFile() const
{
    return this->logfile;
}

void Logger::setLogFile(const std::filesystem::path filename)
{
    std::shared_ptr<spdlog::sinks::sink> fileSink;
    try
    {
        fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                       filename.c_str(),
                       /*truncate = */true
                   );
        fileSink->set_level(static_cast<spdlog::level::level_enum>(getLogLevel()));
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        logger->error("Could not set log file to '{}': {}", filename.c_str(), ex.what());
        return;
    }

    if (logfile.has_value())
    {
        logger->sinks()[1] = fileSink;
    }
    else
    {
        logger->sinks().push_back(fileSink);
    }
}

void Logger::unsetLogFile()
{
    if (logfile.has_value())
    {
        logger->sinks().pop_back();
        logfile.reset();
    }
    else
    {
        logger->warn("Attempting to unset log file when none has been set.");
    }
}

void Logger::makeDefault() const
{
    spdlog::set_default_logger(logger);
}

std::shared_ptr<spdlog::logger> Logger::expose()
{
    return logger;
}

std::shared_ptr<spdlog::sinks::sink> Logger::getConsSink() const
{
    return logger->sinks()[0];
}

std::shared_ptr<spdlog::sinks::sink> Logger::getFileSink() const
{
    if (logfile.has_value())
    {
        return logger->sinks()[1];
    }
    else
    {
        return nullptr;
    }
}

void Logger::trace(const std::string_view msg) const
{
    logger->trace(msg);
}

void Logger::debug(const std::string_view msg) const
{
    logger->debug(msg);
}

void Logger::info(const std::string_view msg) const
{
    logger->info(msg);
}

void Logger::warn(const std::string_view msg) const
{
    logger->warn(msg);
}

void Logger::error(const std::string_view msg) const
{
    logger->error(msg);
}

void Logger::critical(const std::string_view msg) const
{
    logger->critical(msg);
}
