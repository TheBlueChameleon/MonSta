#ifndef ERRORSERVICE_HPP
#define ERRORSERVICE_HPP

#include <string_view>

#include <services/IErrorService.hpp>

namespace ErrorService
{
    void clearError();

    void setError(const ApiStatusCode code, const std::string_view message);

    ApiStatusCode getErrorCode();
    const std::string_view getErrorMessage();

    void terminateAbnormally();
}

#endif // ERRORSERVICE_HPP
