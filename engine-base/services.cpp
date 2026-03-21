#include <HostApi.hpp>

#include "services.hpp"

HostApi* hostApi;

const ILoggerService& loggerService()
{
    return hostApi->loggerService;
}
