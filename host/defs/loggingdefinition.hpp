#ifndef LOGGINGDEFINITION_HPP
#define LOGGINGDEFINITION_HPP

#include <filesystem>
#include <optional>

#include <ILoggerService.hpp>

struct LoggingDefinition
{
    std::optional<std::filesystem::path> logfile  = std::nullopt;
    ILoggerService::LogLevel             loglevel = DEFAULT_LOGGER_LEVEL;
};

#endif // LOGGINGDEFINITION_HPP
