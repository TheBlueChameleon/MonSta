#ifndef ILOGGERSERVICE_H
#define ILOGGERSERVICE_H

struct ILoggerService
{
    enum class LogLevel : int
    {
        TRACE    = 0,
        DEBUG    = 1,
        INFO     = 2,
        WARN     = 3,
        ERROR    = 4,
        CRITICAL = 5,
        OFF      = 6,
        N_LEVELS
    };

    void (*trace)(const char* const msg);
    void (*debug)(const char* const msg);
    void (*info)(const char* const msg);
    void (*warn)(const char* const msg);
    void (*error)(const char* const msg);
    void (*critical)(const char* const msg);
};

constexpr auto DEFAULT_LOGGER_NAME = "MonStaLogger";
constexpr auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
constexpr auto DEFAULT_LOGGER_LEVEL = ILoggerService::LogLevel::TRACE;

#endif // ILOGGERSERVICE_H
