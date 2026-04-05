#ifndef LOGGINGDEFINITION_HPP
#define LOGGINGDEFINITION_HPP

#include <filesystem>
#include <optional>

#include <services/ILoggerService.hpp>

struct LoggingDefinition
{
    const std::optional<std::filesystem::path> logfile  = std::nullopt;
    const ILoggerService::LogLevel             loglevel = DEFAULT_LOGGER_LEVEL;
};

#endif // LOGGINGDEFINITION_HPP
