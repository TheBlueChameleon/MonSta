#include <services/ILoggerService.hpp>

#include "services.hpp"
#include "loggerservice.hpp"

namespace LoggerService
{
    void trace(const std::string_view msg)
    {
        loggerService().trace(msg.data());
        rethrowHostError();
    }

    void debug(const std::string_view msg)
    {
        loggerService().trace(msg.data());
        rethrowHostError();
    }

    void info(const std::string_view msg)
    {
        loggerService().info(msg.data());
        rethrowHostError();
    }

    void warn(const std::string_view msg)
    {
        loggerService().warn(msg.data());
        rethrowHostError();
    }

    void error(const std::string_view msg)
    {
        loggerService().error(msg.data());
        rethrowHostError();
    }

    void critical(const std::string_view msg)
    {
        loggerService().critical(msg.data());
        rethrowHostError();
    }
}
