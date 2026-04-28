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

    const IRngService& rngService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->rngService;
    }

    const IVersionService& versionService()
    {
        EngineBase::_hostApi->errorService.clearError;
        return EngineBase::_hostApi->versionService;
    }

}
