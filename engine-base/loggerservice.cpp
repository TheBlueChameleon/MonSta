#include <ILoggerService.hpp>

#include "services.hpp"
#include "loggerservice.hpp"

void LoggerService::trace(const char* const msg)
{
    loggerService().trace(msg);
}

void LoggerService::debug(const char* const msg)
{
    loggerService().trace(msg);
}

void LoggerService::info(const char* const msg)
{
    loggerService().info(msg);
}

void LoggerService::warn(const char* const msg)
{
    loggerService().warn(msg);
}

void LoggerService::error(const char* const msg)
{
    loggerService().error(msg);
}

void LoggerService::critical(const char* const msg)
{
    loggerService().critical(msg);
}
