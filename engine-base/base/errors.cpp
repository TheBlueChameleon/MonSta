#include "services/errorservice.hpp"

#include "errors.hpp"
// ========================================================================== //
// Base Error

EngineError::EngineError(std::string_view message) :
    EngineError(ApiStatusCode::CRITICAL_ABORT, message)
{}

EngineError::EngineError(const int errorCode, std::string_view message) :
    errorCode(errorCode),
    std::runtime_error(message.data())
{}

int EngineError::getErrorCode() const
{
    return errorCode;
}

// ========================================================================== //
// Pre-Coded Errors

InvalidUserInput::InvalidUserInput() :
    InvalidUserInput("Invalid user input")
{}

InvalidUserInput::InvalidUserInput(const std::string_view msg) :
    EngineError(ApiStatusCode::INVALID_USER_INPUT, msg)
{}

IllegalStateError::IllegalStateError() :
    IllegalStateError("Illegal State")
{}

IllegalStateError::IllegalStateError(const std::string_view msg) :
    EngineError(ApiStatusCode::ILLEGAL_STATE, msg)
{}

IllegalArgumentError::IllegalArgumentError() :
    IllegalArgumentError("Illegal Argument")
{}

IllegalArgumentError::IllegalArgumentError(const std::string_view msg) :
    EngineError(ApiStatusCode::ILLEGAL_ARGUMENT, msg)
{}

MissingParameterError::MissingParameterError() :
    MissingParameterError("Missing Parameter")
{}

MissingParameterError::MissingParameterError(const std::string_view msg) :
    EngineError(ApiStatusCode::MISSING_PARAMETER, msg)
{}

NotImplementedError::NotImplementedError() :
    NotImplementedError("Not implemented")
{}

NotImplementedError::NotImplementedError(const std::string_view msg) :
    EngineError(ApiStatusCode::NOT_IMPLEMENTED, msg)
{}

MultipleErrors::MultipleErrors() :
    MultipleErrors("Multiple Errors")
{}

MultipleErrors::MultipleErrors(const std::string_view msg) :
    EngineError(ApiStatusCode::MULTIPLE_ERRORS, msg)
{}

// ========================================================================== //
// Aux Functions

namespace EngineBase
{
    void passExceptionToHost(const EngineError& e)
    {
        ErrorService::setError(e.getErrorCode(), e.what());
        ErrorService::terminateAbnormally();
    }
}
