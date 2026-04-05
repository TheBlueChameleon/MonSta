#ifndef IERRORSERVICE_HPP
#define IERRORSERVICE_HPP

#include <ApiStatusCode.hpp>

struct IErrorService
{
    void (*clearError)();

    void (*setError)(const ApiStatusCode code, const char* const message);

    ApiStatusCode(*getErrorCode)();
    const char* const(*getErrorMessage)();
};

#endif // IERRORSERVICE_HPP
