#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

class CriticalAbort : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        CriticalAbort() :
            std::runtime_error("Critical abort. See the logs for possible reasons.")
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

class ClientError : public std::runtime_error
{
    public:
        using std::runtime_error::runtime_error;

        ClientError() :
            std::runtime_error("Client side abort. See the logs for possible reasons.")
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

#endif // ERRORS_HPP
