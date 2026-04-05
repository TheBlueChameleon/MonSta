#include "errorservice.hpp"
#include "errorservice_dlx.hpp"

namespace ErrorService
{
    void HOST_API_CALL clearError_dlx()
    {
        clearError();
    }

    void HOST_API_CALL setError_dlx(
        const ApiStatusCode code,
        const char* const message
    )
    {
        setError(code, message);
    }

    ApiStatusCode HOST_API_CALL getErrorCode_dlx()
    {
        return getErrorCode();
    }

    const char* const HOST_API_CALL getErrorMessage_dlx()
    {
        return getErrorMessage().data();
    }
}
