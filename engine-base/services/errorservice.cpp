#include "errorservice.hpp"
#include "services.hpp"

namespace ErrorService
{
    void clearError()
    {
        errorService().clearError();
    }

    void setError(const ApiStatusCode code, const char* const message)
    {
        errorService().setError(code, message);
    }

    ApiStatusCode getErrorCode()
    {
        return errorService().getErrorCode();
    }

    const char* const getErrorMessage()
    {
        return errorService().getErrorMessage();
    }
}
