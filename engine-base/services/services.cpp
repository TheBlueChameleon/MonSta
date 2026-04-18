#include <string>

#include <HostApi.hpp>

#include "services/services.hpp"

#include "base/errors.hpp"
#include "base/globals.hpp"

namespace Services
{
    const ICsvService& csvService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->csvService;
    }

    const IErrorService& errorService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->errorService;
    }

    const IFileService& fileService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->fileService;
    }

    const IJsonService& jsonService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->jsonService;
    }

    const ILoggerService& loggerService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->loggerService;
    }

    const IMemoryService& memoryService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->memoryService;
    }

    void rethrowHostError()
    {
        const auto errCode = EngineBase::_hostApi->errorService.getErrorCode();
        if (errCode != ApiStatusCode::SUCCESS)
        {
            std::string errorMessage = EngineBase::_hostApi->errorService.getErrorMessage();
            EngineBase::_hostApi->errorService.clearError();
            throw EngineError(errCode, errorMessage.data());
        }
    }
}
