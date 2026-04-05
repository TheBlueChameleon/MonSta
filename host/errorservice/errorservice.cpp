#include <string>

#include "errorservice.hpp"
#include "errorservice_dlx.hpp"

namespace ErrorService
{
    ApiStatusCode errorCode = ApiStatusCode::SUCCESS;
    std::string errorMessage;

    const IErrorService exportService()
    {
        return IErrorService
        {
            clearError_dlx,
            setError_dlx,
            getErrorCode_dlx,
            getErrorMessage_dlx,
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
}
