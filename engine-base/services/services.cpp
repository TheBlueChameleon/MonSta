#include <HostApi.hpp>

#include "services/services.hpp"

#include "globals.hpp"

const IErrorService errorService()
{
    return Globals::hostApi->errorService;
}

const IJsonService& jsonService()
{
    return Globals::hostApi->jsonService;
}

const ILoggerService& loggerService()
{
    return Globals::hostApi->loggerService;
}
