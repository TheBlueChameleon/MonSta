#include "errorservice.hpp"

namespace ErrorService
{
    ApiStatusCode errorCode = ApiStatusCode::SUCCESS;
    std::string errorMessage;

    const IErrorService exportService()
    {
        return IErrorService
        {
            clearError,
            setError_dlx,
            getErrorCode,
            getErrorMessage,
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

    void setError_dlx(const ApiStatusCode code, const char* const message)
    {
        setError(code, message);
    }

    ApiStatusCode getErrorCode()
    {
        return errorCode;
    }

    const char* const getErrorMessage()
    {
        return errorMessage.data();
    }

}
