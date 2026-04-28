#include <string>
using namespace std::string_literals;

#include "errorservice/errors.hpp"

#include "loggerservice.hpp"
#include "loggerservice_dlx.hpp"

namespace LoggerService
{
    Logger instance;

    ILoggerService exportService()
    {
        return ILoggerService(
                   LoggerService::trace_dlx,
                   LoggerService::debug_dlx,
                   LoggerService::info_dlx,
                   LoggerService::warn_dlx,
                   LoggerService::error_dlx,
                   LoggerService::critical_dlx
               );
    }

    Logger& getInstance()
    {
        return instance;
    }

    ILoggerService::LogLevel getLogLevelFromName(const std::string_view name)
    {
        // *INDENT-OFF*
        if (name == ILoggerService::LOGLEVELNAME_TRACE)    {return ILoggerService::LogLevel::TRACE;}
        if (name == ILoggerService::LOGLEVELNAME_DEBUG)    {return ILoggerService::LogLevel::DEBUG;}
        if (name == ILoggerService::LOGLEVELNAME_INFO)     {return ILoggerService::LogLevel::INFO;}
        if (name == ILoggerService::LOGLEVELNAME_WARNING)  {return ILoggerService::LogLevel::WARN;}
        if (name == ILoggerService::LOGLEVELNAME_ERROR)    {return ILoggerService::LogLevel::ERROR;}
        if (name == ILoggerService::LOGLEVELNAME_CRITICAL) {return ILoggerService::LogLevel::CRITICAL;}
        if (name == ILoggerService::LOGLEVELNAME_OFF)      {return ILoggerService::LogLevel::OFF;}
        // *INDENT-ON*

        throw IllegalHostStateException("Unknown log level: "s + name.data());
    }

    void setLogLevel(const ILoggerService::LogLevel level)
    {
        instance.setLogLevel(level);
    }

    void setLogFile(const std::filesystem::__cxx11::path filename)
    {
        instance.setLogFile(filename);
    }

    void trace(const std::string_view msg)
    {
        instance.trace(msg);
    }

    void debug(const std::string_view msg)
    {
        instance.debug(msg);
    }

    void info(const std::string_view msg)
    {
        instance.info(msg);
    }

    void warn(const std::string_view msg)
    {
        instance.warn(msg);
    }

    void error(const std::string_view msg)
    {
        instance.error(msg);
    }

    void critical(const std::string_view msg)
    {
        instance.critical(msg);
    }
}
