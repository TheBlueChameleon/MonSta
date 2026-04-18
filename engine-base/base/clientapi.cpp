#include <iostream>
#include <string>

#include <HostApi.hpp>
#include <CallingConventions.hpp>
#include <ClientApi.hpp>

#include "services/services.hpp"

#include "globals.hpp"

static bool allErrorServicesPresent(const IErrorService& es)
{
    // *INDENT-OFF*
    if (es.clearError      == nullptr) {return false;}
    if (es.getErrorCode    == nullptr) {return false;}
    if (es.getErrorMessage == nullptr) {return false;}
    if (es.setError        == nullptr) {return false;}
    // *INDENT-ON*

    return true;
}
static bool allLoggerServicesPresent(const ILoggerService& ls)
{
    return true;
}
static bool allVersionServicesPresent(const IVersionService& vu)
{
    // *INDENT-OFF*
    if (vu.equal == nullptr)            {return false;}
    if (vu.notEqual == nullptr)         {return false;}
    if (vu.lessThan == nullptr)         {return false;}
    if (vu.lessOrEqual == nullptr)      {return false;}
    if (vu.greaterThan == nullptr)      {return false;}
    if (vu.greaterOrEqual == nullptr)   {return false;}
    if (vu.to_string == nullptr)        {return false;}
    // *INDENT-ON*

    return true;
}

static bool abortInit(const HostApi* hostApi, const char* const msg)
{
    hostApi->errorService.setError(
        ApiStatusCode::CLIENT_INITIALIZATION_ERROR,
        msg
    );
    hostApi->loggerService.critical(msg);

    return false;
}

HOST_API_EXPORT
{
    bool HOST_API_CALL init(HostApi* hostApi)
    {
        if (!allErrorServicesPresent(hostApi->errorService))
        {
            std::cerr << "ErrorService was not initialized!" << std::endl;
            return false;
        }

        if (!allLoggerServicesPresent(hostApi->loggerService))
        {
            hostApi->errorService.setError(
                ApiStatusCode::CLIENT_INITIALIZATION_ERROR,
                "Logger was not initialized!"
            );
            std::cerr << hostApi->errorService.getErrorMessage() << std::endl;
            return false;
        }

        if (!allVersionServicesPresent(hostApi->versionService))
        {
            return abortInit(hostApi, "Not all VersionUtils have been initialized!");
        }

        EngineBase::_hostApi = hostApi;

        return init_engine();
    }

    bool HOST_API_CALL hasFeature(const char* const featureTag)
    {
        return EngineBase::supportedFeatures.contains(featureTag);
    }

    void HOST_API_CALL terminateAbnormally()
    {
        EngineBase::abnormalTerminationRequest = true;
    }

    void HOST_API_CALL setOverwrite(const bool overwrite)
    {
        EngineBase::overwriteFiles = overwrite;
    }

    void HOST_API_CALL setCreateDirectories(const bool createDirectories)
    {
        EngineBase::createDirectories = createDirectories;
    }

    void HOST_API_CALL setDryMode(const bool dryMode)
    {
        EngineBase::dryMode = dryMode;
    }
}
