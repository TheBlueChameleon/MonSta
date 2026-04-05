#ifndef ERRORSERVICE_DLX_HPP
#define ERRORSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IErrorService.hpp>

namespace ErrorService
{
    void HOST_API_CALL clearError_dlx();
    void HOST_API_CALL setError_dlx(const ApiStatusCode code, const char* const message);
    ApiStatusCode HOST_API_CALL getErrorCode_dlx();
    const char* const HOST_API_CALL getErrorMessage_dlx();
}

#endif // ERRORSERVICE_DLX_HPP
