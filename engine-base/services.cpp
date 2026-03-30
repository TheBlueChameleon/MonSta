#include <HostApi.hpp>

#include "globals.hpp"
#include "services.hpp"

const ILoggerService& loggerService()
{
    return Globals::hostApi->loggerService;
}
