#include "errors.hpp"

EngineError::EngineError(const ApiStatusCode errorCode) :
    EngineError(errorCode, "Engine Error")
{}

EngineError::EngineError(const ApiStatusCode errorCode, std::string_view message) :
    errorCode(errorCode),
    std::runtime_error(message.data())
{}

ApiStatusCode EngineError::getErrorCode() const
{
    return errorCode;
}
