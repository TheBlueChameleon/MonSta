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
        int errorCode = ApiStatusCode::CRITICAL_ABORT;

    public:
        using std::runtime_error::runtime_error;

        AbstractError(const int errorCode);
        AbstractError(const int errorCode, std::string_view message);

        int getErrorCode() const;
};

// .......................................................................... //

class HostSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        HostSideError(const int errorCode);
        HostSideError(const int errorCode, const std::string_view msg);
};

class ClientSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        ClientSideError(const int errorCode);
        ClientSideError(const int errorCode, std::string_view message);
};

class UserSideError : public AbstractError
{
    public:
        using AbstractError::AbstractError;

        UserSideError(const int errorCode);
        UserSideError(const int errorCode, std::string_view message);
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

class IOError : public HostSideError
{
    public:
        using HostSideError::HostSideError;

        IOError();
        IOError(const std::string_view msg);
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
