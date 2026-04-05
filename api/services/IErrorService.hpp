#ifndef IERRORSERVICE_HPP
#define IERRORSERVICE_HPP

#include <ApiStatusCode.hpp>
#include <CallingConventions.hpp>

struct IErrorService
{
    void (HOST_API_CALL* const clearError)();
    void (HOST_API_CALL* const setError)(const ApiStatusCode code, const char* const message);
    ApiStatusCode(HOST_API_CALL* const getErrorCode)();
    const char* const(HOST_API_CALL* const getErrorMessage)();
};

#endif // IERRORSERVICE_HPP
