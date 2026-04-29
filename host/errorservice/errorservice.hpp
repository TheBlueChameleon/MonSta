#ifndef ERRORSERVICE_HPP
#define ERRORSERVICE_HPP

#include <string_view>

#include <services/IErrorService.hpp>

namespace ErrorService
{
    const IErrorService exportService();

    void clearError();
    void setError(const int code, const std::string_view message);
    int getErrorCode();
    const std::string_view getErrorMessage();

    void terminateAbnormally();
}

#endif // ERRORSERVICE_HPP
