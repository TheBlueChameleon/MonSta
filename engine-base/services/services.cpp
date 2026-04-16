#include <string>

#include <HostApi.hpp>

#include "services/services.hpp"

#include "errors.hpp"
#include "globals.hpp"

const IErrorService& errorService()
{
    return Globals::_hostApi->errorService;
}

const IFileService& fileService()
{
    return Globals::_hostApi->fileService;
}

const IJsonService& jsonService()
{
    return Globals::_hostApi->jsonService;
}

const ILoggerService& loggerService()
{
    return Globals::_hostApi->loggerService;
}

const IMemoryService& memoryService()
{
    return Globals::_hostApi->memoryService;
}

void rethrowHostError()
{
    const auto errCode = Globals::_hostApi->errorService.getErrorCode();
    if (errCode != ApiStatusCode::SUCCESS)
    {
        std::string errorMessage = Globals::_hostApi->errorService.getErrorMessage();
        Globals::_hostApi->errorService.clearError();

        throw EngineError(errCode, errorMessage.data());
    }
}
