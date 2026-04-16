#ifndef IERRORSERVICE_HPP
#define IERRORSERVICE_HPP

#include <ApiStatusCode.hpp>
#include <CallingConventions.hpp>

struct IErrorService
{
    void (*const HOST_API_CALL clearError)();
    void (*const HOST_API_CALL setError)(const ApiStatusCode code, const char* const message);
    ApiStatusCode(*const HOST_API_CALL getErrorCode)();
    const char* const(*const HOST_API_CALL getErrorMessage)();

    void (*const HOST_API_CALL terminateAbnormally)();
};

#endif // IERRORSERVICE_HPP
