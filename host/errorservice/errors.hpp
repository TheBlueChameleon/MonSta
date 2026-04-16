#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>
using namespace std::string_literals;

#include <ApiStatusCode.hpp>

// ========================================================================== //
// Base Errors

class AbstractError : public std::runtime_error
{
    protected:
        ApiStatusCode errorCode = ApiStatusCode::CRITICAL_ABORT;

    public:
        using std::runtime_error::runtime_error;

        AbstractError(const ApiStatusCode errorCode);
        AbstractError(const ApiStatusCode errorCode, std::string_view message);

        ApiStatusCode getErrorCode() const;
};

// .......................................................................... //

class HostSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        HostSideError(const ApiStatusCode errorCode);
        HostSideError(const ApiStatusCode errorCode, const std::string_view msg);
};

class ClientSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        ClientSideError(const ApiStatusCode errorCode);
        ClientSideError(const ApiStatusCode errorCode, std::string_view message);
};

class UserSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        UserSideError(const ApiStatusCode errorCode);
        UserSideError(const ApiStatusCode errorCode, std::string_view message);
};

// ========================================================================== //
// User Side Errors

class InvalidUserInput : public UserSideError
{
    public:
        using UserSideError::UserSideError;

        InvalidUserInput();
        InvalidUserInput(const std::string_view msg);
};

// ========================================================================== //
// Host Side Errors

class CriticalAbort : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        CriticalAbort();
        CriticalAbort(const std::string_view msg);
};

class HostInitializationError : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        HostInitializationError();
        HostInitializationError(const std::string_view msg);
};

class IllegalHostStateException : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        IllegalHostStateException();
        IllegalHostStateException(const std::string_view msg);
};

class LookupError : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        LookupError();
        LookupError(const std::string_view msg);
};

class JsonError : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        JsonError();
        JsonError(const std::string_view msg);
};

class CsvError : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        CsvError();
        CsvError(const std::string_view msg);
};

// ========================================================================== //
// Client Side Errors

class ClientInitializationError : public ClientSideError
{
    public:
        using ClientSideError::ClientSideError;

        ClientInitializationError();
        ClientInitializationError(const std::string_view msg);
};

class ClientRequestError : public ClientSideError
{
    public:
        using ClientSideError::ClientSideError;

        ClientRequestError();
        ClientRequestError(const std::string_view msg);
};

#endif // ERRORS_HPP
