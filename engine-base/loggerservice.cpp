#include "loggerservice.hpp"

ILoggerService loggerService;

void trace(const char* const msg)
{
    loggerService.trace(msg);
}

void debug(const char* const msg)
{
    loggerService.trace(msg);
}

void info(const char* const msg)
{
    loggerService.info(msg);
}

void warn(const char* const msg)
{
    loggerService.warn(msg);
}

void error(const char* const msg)
{
    loggerService.error(msg);
}

void critical(const char* const msg)
{
    loggerService.critical(msg);
}
