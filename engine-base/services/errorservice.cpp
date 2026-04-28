#include "HostApi.hpp"

#include "base/globals.hpp"
#include "base/errors.hpp"

#include "errorservice.hpp"
#include "services.hpp"

using namespace Services;

namespace ErrorService
{
    void clearError()
    {
        errorService().clearError();
    }

    void setError(const ApiStatusCode code, const std::string_view message)
    {
        errorService().setError(code, message.data());
    }

    ApiStatusCode getErrorCode()
    {
        return errorService().getErrorCode();
    }

    const std::string_view getErrorMessage()
    {
        return errorService().getErrorMessage();
    }

    void terminateAbnormally()
    {
        return errorService().terminateAbnormally();
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
