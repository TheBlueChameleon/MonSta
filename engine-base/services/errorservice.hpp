#ifndef ERRORSERVICE_HPP
#define ERRORSERVICE_HPP

#include <IErrorService.hpp>

namespace ErrorService
{
    void clearError();

    void setError(const ApiStatusCode code, const char* const message);

    ApiStatusCode getErrorCode();
    const char* const getErrorMessage();
}

#endif // ERRORSERVICE_HPP
