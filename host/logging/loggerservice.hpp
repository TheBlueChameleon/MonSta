#ifndef LOGGERSERVICE_HPP
#define LOGGERSERVICE_HPP

#include "../operationmodes/defs/loggingdefinition.hpp"

#include "../logging/logger.hpp"

class LoggerService
{
    private:
        static Logger instance;

        LoggerService();

    public:
        static Logger& getInstance();

        static void setup(const LoggingDefinition def);

        static void trace(const char* const msg);
        static void debug(const char* const msg);
        static void info(const char* const msg);
        static void warn(const char* const msg);
        static void error(const char* const msg);
        static void critical(const char* const msg);

        template <typename... Args>
        static void traceF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::trace(msg.c_str());
        }

        template <typename... Args>
        static void debugF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::debug(msg.c_str());
        }

        template <typename... Args>
        static void infoF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::info(msg.c_str());
        }

        template <typename... Args>
        static void warnF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::warn(msg.c_str());
        }

        template <typename... Args>
        static void errorF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::error(msg.c_str());
        }

        template <typename... Args>
        static void criticalF(std::format_string<Args...> fmt, Args&& ...args)
        {
            const auto msg = std::format(fmt, std::forward<Args>(args)...);
            LoggerService::critical(msg.c_str());
        }
};

#endif // LOGGERSERVICE_HPP
