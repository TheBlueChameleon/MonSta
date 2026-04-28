#ifndef ILOGGERSERVICE_H
#define ILOGGERSERVICE_H

#include <CallingConventions.hpp>

struct ILoggerService
{
    static constexpr auto LOGLEVELNAME_TRACE    = "trace";
    static constexpr auto LOGLEVELNAME_DEBUG    = "debug";
    static constexpr auto LOGLEVELNAME_INFO     = "info";
    static constexpr auto LOGLEVELNAME_WARNING  = "warning";
    static constexpr auto LOGLEVELNAME_ERROR    = "error";
    static constexpr auto LOGLEVELNAME_CRITICAL = "critical";
    static constexpr auto LOGLEVELNAME_OFF      = "off";

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

    void (HOST_API_CALL* const trace)(const char* const msg);
    void (HOST_API_CALL* const debug)(const char* const msg);
    void (HOST_API_CALL* const info)(const char* const msg);
    void (HOST_API_CALL* const warn)(const char* const msg);
    void (HOST_API_CALL* const error)(const char* const msg);
    void (HOST_API_CALL* const critical)(const char* const msg);
};

const auto DEFAULT_LOGGER_NAME = "MonStaLogger";
const auto DEFAULT_LOGGER_PATTERN = "[%Y-%m-%d %H:%M:%S] [%l] %v";
const auto DEFAULT_LOGGER_LEVEL = ILoggerService::LogLevel::TRACE;

#endif // ILOGGERSERVICE_H
