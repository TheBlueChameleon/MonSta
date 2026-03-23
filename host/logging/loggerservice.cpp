#include "../operationmodes/shared/defs/loggingdefinition.hpp"

#include "loggerservice.hpp"

namespace LoggerService
{
    Logger instance;

    Logger& getInstance()
    {
        return instance;
    }

    void setup(const LoggingDefinition def)
    {
        if (def.logfile.has_value())
        {
            instance.setLogFile(def.logfile.value());
        }

        instance.setLogLevel(def.loglevel);
    }

    void trace(const char* const msg)
    {
        instance.trace(msg);
    }

    void debug(const char* const msg)
    {
        instance.debug(msg);
    }

    void info(const char* const msg)
    {
        instance.info(msg);
    }

    void warn(const char* const msg)
    {
        instance.warn(msg);
    }

    void error(const char* const msg)
    {
        instance.error(msg);
    }

    void critical(const char* const msg)
    {
        instance.critical(msg);
    }
}
