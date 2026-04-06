#include "errorservice.hpp"
#include "services.hpp"

namespace ErrorService
{
    void clearError()
    {
        errorService().clearError();
    }

    void setError(const ApiStatusCode code, const std::string_view message)
    {
        errorService().setError(code, message.data());
    }

    ApiStatusCode getErrorCode()
    {
        return errorService().getErrorCode();
    }

    const std::string_view getErrorMessage()
    {
        return errorService().getErrorMessage();
    }
}
