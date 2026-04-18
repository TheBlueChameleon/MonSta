#include <string>

#include "errors.hpp"
#include "errorservice.hpp"
#include "errorservice_dlx.hpp"

namespace ErrorService
{
    thread_local ApiStatusCode errorCode = ApiStatusCode::SUCCESS;
    thread_local std::string errorMessage;

    const IErrorService exportService()
    {
        return IErrorService
        {
            clearError_dlx,
            setError_dlx,
            getErrorCode_dlx,
            getErrorMessage_dlx,
            terminateAbnormally_dlx
        };
    }

    void clearError()
    {
        errorCode = ApiStatusCode::SUCCESS;
        errorMessage.clear();
    }

    void setError(const ApiStatusCode code, const std::string_view message)
    {
        errorCode = code;
        errorMessage = message;
    }

    ApiStatusCode getErrorCode()
    {
        return errorCode;
    }

    const std::string_view getErrorMessage()
    {
        return errorMessage;
    }

    void terminateAbnormally()
    {
        const auto errCode = getErrorCode();
        if (errCode != ApiStatusCode::SUCCESS)
        {
            std::string errorMessage = getErrorMessage().data();
            clearError();

            throw ClientSideError(errCode, errorMessage.data());
        }
    }
}
