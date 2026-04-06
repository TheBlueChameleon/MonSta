#include <string>

#include <HostApi.hpp>

#include "services/services.hpp"

#include "errors.hpp"
#include "globals.hpp"

namespace Globals
{
    extern HostApi* _hostApi;
}

HostApiProxy::HostApiProxy() :
    hostApi(Globals::_hostApi)
{}

HostApiProxy::~HostApiProxy()
{
    rethrowHostError();
}

HostApi& HostApiProxy::get()
{
    return *hostApi;
}

void HostApiProxy::rethrowHostError()
{
    const auto errCode = hostApi->errorService.getErrorCode();
    if (errCode != ApiStatusCode::SUCCESS)
    {
        std::string errorMessage = hostApi->errorService.getErrorMessage();
        hostApi->errorService.clearError();

        throw EngineError(errCode, errorMessage.data());
    }
}

const IErrorService errorService()
{
    return HostApiProxy().get().errorService;
}

const IJsonService& jsonService()
{
    return HostApiProxy().get().jsonService;
}

const ILoggerService& loggerService()
{
    return HostApiProxy().get().loggerService;
}
