#include <string>

#include <HostApi.hpp>

#include "services/services.hpp"

#include "errors.hpp"
#include "globals.hpp"

void autoThrow()
{
    const auto errCode = Globals::hostApi->errorService.getErrorCode();
    if (errCode != ApiStatusCode::SUCCESS)
    {
        std::string errorMessage = Globals::hostApi->errorService.getErrorMessage();
        Globals::hostApi->errorService.clearError();

        throw EngineError(errCode, errorMessage.data());
    }
}

const IErrorService errorService()
{
    autoThrow();
    return Globals::hostApi->errorService;
}

const IJsonService& jsonService()
{
    autoThrow();
    return Globals::hostApi->jsonService;
}

const ILoggerService& loggerService()
{
    autoThrow();
    return Globals::hostApi->loggerService;
}
