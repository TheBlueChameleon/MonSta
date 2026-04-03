#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>
#include <string>
using namespace std::string_literals;

#include <ClientReturnCodes.hpp>

class CriticalAbort : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        CriticalAbort() :
            std::runtime_error("Critical abort. See the logs for possible reasons.")
        {}
};

class IllegalStateException : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        IllegalStateException() :
            std::runtime_error("Illegal state. Please report what you did to <the dev>.")
        {}
};

class LookupError : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        LookupError() :
            std::runtime_error("Requested Item not found. See the logs for possible reasons.")
        {}
};

class ClientRequestError : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        ClientRequestError() :
            std::runtime_error("Client requested illegal operation. See the logs for possible reasons.")
        {}
};

class ClientSideError : public std::runtime_error
{
    protected:
        ClientReturnCode errorCode;

    public:
        using std::runtime_error::runtime_error;

        ClientSideError(ClientReturnCode errorCode) :
            std::runtime_error("Client side abort, error code "s +
                               std::to_string(static_cast<int>(errorCode)) + "\n" +
                               "See the logs for possible reasons.")
        {}

        ClientSideError(
            ClientReturnCode errorCode,
            std::string_view message
        ) :
            std::runtime_error("Client side abort, error code "s +
                               std::to_string(static_cast<int>(errorCode)) + "\n" +
                               message.data())
        {}
};

#endif // ERRORS_HPP
