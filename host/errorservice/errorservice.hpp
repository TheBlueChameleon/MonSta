#ifndef ERRORSERVICE_HPP
#define ERRORSERVICE_HPP

#include <string>
#include <string_view>

#include <services/IErrorService.hpp>

namespace ErrorService
{
    extern ApiStatusCode errorCode;
    extern std::string errorMessage;

    const IErrorService exportService();

    void clearError();

    void setError(const ApiStatusCode code, const std::string_view message);
    void setError_dlx(const ApiStatusCode code, const char* const message);

    ApiStatusCode getErrorCode();
    const char* const getErrorMessage();
}

#endif // ERRORSERVICE_HPP
