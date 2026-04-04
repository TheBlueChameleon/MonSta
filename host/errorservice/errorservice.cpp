#include "errorservice.hpp"

namespace ErrorService
{
    ClientReturnCode errorCode = ClientReturnCode::SUCCESS;
    std::string errorMessage;

    const IErrorService exportService()
    {
        return IErrorService
        {
            clearError,
            setError,
            getErrorCode,
            getErrorMessage,
        };
    }

    void clearError()
    {
        errorCode = ClientReturnCode::SUCCESS;
        errorMessage.clear();
    }

    void setError(const ClientReturnCode code, const char* const message)
    {
        errorCode = code;
        errorMessage = message;
    }

    ClientReturnCode getErrorCode()
    {
        return errorCode;
    }

    const char* const getErrorMessage()
    {
        return errorMessage.data();
    }
}
