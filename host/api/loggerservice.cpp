#include "loggerservice.hpp"

Logger LoggerService::instance;

LoggerService::LoggerService()
{
    instance.makeDefault();
}

Logger LoggerService::getInstance()
{
    return instance;
}

void LoggerService::trace(const char* const msg)
{
    instance.trace(msg);
}

void LoggerService::debug(const char* const msg)
{
    instance.debug(msg);
}

void LoggerService::info(const char* const msg)
{
    instance.info(msg);
}

void LoggerService::warn(const char* const msg)
{
    instance.warn(msg);
}

void LoggerService::error(const char* const msg)
{
    instance.error(msg);
}

void LoggerService::critical(const char* const msg)
{
    instance.critical(msg);
}
