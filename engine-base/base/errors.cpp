#include "services/errorservice.hpp"

#include "errors.hpp"

EngineError::EngineError(const int errorCode) :
    EngineError(errorCode, "Engine Error")
{}

EngineError::EngineError(const int errorCode, std::string_view message) :
    errorCode(errorCode),
    std::runtime_error(message.data())
{}

int EngineError::getErrorCode() const
{
    return errorCode;
}

namespace EngineBase
{
    void passExceptionToHost(const EngineError& e)
    {
        ErrorService::setError(e.getErrorCode(), e.what());
        ErrorService::terminateAbnormally();
    }
}
