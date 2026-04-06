#include <services/ILoggerService.hpp>

#include "services.hpp"
#include "loggerservice.hpp"

namespace LoggerService
{
    void trace(const std::string_view msg)
    {
        loggerService().trace(msg.data());
    }

    void debug(const std::string_view msg)
    {
        loggerService().trace(msg.data());
    }

    void info(const std::string_view msg)
    {
        loggerService().info(msg.data());
    }

    void warn(const std::string_view msg)
    {
        loggerService().warn(msg.data());
    }

    void error(const std::string_view msg)
    {
        loggerService().error(msg.data());
    }

    void critical(const std::string_view msg)
    {
        loggerService().critical(msg.data());
    }
}
