#include <string>
using namespace std::string_literals;

#include "errors.hpp"

// ========================================================================== //
// Base Errors

AbstractError::AbstractError(const ApiStatusCode errorCode) :
    AbstractError(errorCode,
                  "Abort due to internal error. See the logs for possible reasons."
                 )
{}

AbstractError::AbstractError(const ApiStatusCode errorCode, std::string_view message) :
    errorCode(errorCode),
    std::runtime_error("Error code "s +
                       std::to_string(static_cast<int>(errorCode)) + "\n" +
                       message.data() + "\n" +
                       "See the logs for possible reasons.")
{}

ApiStatusCode AbstractError::getErrorCode() const
{
    return errorCode;
}

// -------------------------------------------------------------------------- //

HostSideError::HostSideError(const ApiStatusCode errorCode) :
    HostSideError(errorCode, "Host side abort.")
{}

HostSideError::HostSideError(const ApiStatusCode errorCode, const std::string_view msg) :
    AbstractError(ApiStatusCode::CRITICAL_ABORT, msg)
{}

// -------------------------------------------------------------------------- //

ClientSideError::ClientSideError(const ApiStatusCode errorCode) :
    ClientSideError(errorCode, "Client side abort.")
{}

ClientSideError::ClientSideError(const ApiStatusCode errorCode, std::string_view message) :
    AbstractError(errorCode, message)
{}

UserSideError::UserSideError(const ApiStatusCode errorCode) :
    UserSideError(errorCode, "Invalid user input.")
{}

UserSideError::UserSideError(const ApiStatusCode errorCode, std::string_view message) :
    AbstractError(errorCode, message)
{}

// ========================================================================== //
// User Side Errors

InvalidUserInput::InvalidUserInput() :
    InvalidUserInput("Invalid user input.")
{}

InvalidUserInput::InvalidUserInput(const std::string_view msg) :
    UserSideError(ApiStatusCode::INVALID_USER_INPUT, msg)
{}

// ========================================================================== //
// Host Side Errors

CriticalAbort::CriticalAbort() :
    CriticalAbort("Critical abort.")
{}

CriticalAbort::CriticalAbort(const std::string_view msg) :
    HostSideError(ApiStatusCode::CRITICAL_ABORT, msg)
{}

HostInitializationError::HostInitializationError() :
    HostInitializationError("Could not initialize host.")
{}

HostInitializationError::HostInitializationError(const std::string_view msg) :
    HostSideError(ApiStatusCode::HOST_INITIALIZATION_ERROR, msg)
{}

IllegalHostStateException::IllegalHostStateException() :
    IllegalHostStateException("Illegal state. Please report what you did to <the dev>.")
{}

IllegalHostStateException::IllegalHostStateException(const std::string_view msg) :
    HostSideError(ApiStatusCode::ILLEGAL_HOST_STATE, msg)
{}

LookupError::LookupError() :
    LookupError("Requested Item not found.")
{}

LookupError::LookupError(const std::string_view msg) :
    HostSideError(ApiStatusCode::LOOKUP_ERROR, msg)
{}

JsonError::JsonError() :
    JsonError("JSON handling error")
{}

JsonError::JsonError(const std::string_view msg) :
    HostSideError(ApiStatusCode::JSON_ERROR, msg)
{}

CsvError::CsvError() :
    CsvError("CSV handling error")
{}

CsvError::CsvError(const std::string_view msg) :
    HostSideError(ApiStatusCode::CSV_ERROR, msg)
{}

// ========================================================================== //
// Client Side Errors

ClientInitializationError::ClientInitializationError() :
    ClientInitializationError("Could not initialize client.")
{}

ClientInitializationError::ClientInitializationError(const std::string_view msg) :
    ClientSideError(ApiStatusCode::CLIENT_INITIALIZATION_ERROR, msg)
{}

ClientRequestError::ClientRequestError() :
    ClientRequestError("Client requested illegal operation.")
{}

ClientRequestError::ClientRequestError(const std::string_view msg) :
    ClientSideError(ApiStatusCode::INVALID_REQUEST_BY_CLIENT, msg)
{}
