#ifndef ERRORSERVICE_HPP
#define ERRORSERVICE_HPP

#include <string>

#include <IErrorService.hpp>

namespace ErrorService
{
    extern ClientReturnCode errorCode;
    extern std::string errorMessage;

    const IErrorService exportService();

    void clearError();

    void setError(const ClientReturnCode code, const char* const message);

    ClientReturnCode getErrorCode();
    const char* const getErrorMessage();
}

#endif // ERRORSERVICE_HPP
