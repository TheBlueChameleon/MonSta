#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

#include <ApiStatusCode.hpp>

class EngineError : public std::runtime_error
{
    protected:
        ApiStatusCode errorCode = ApiStatusCode::ILLEGAL_CLIENT_STATE;

    public:
        using std::runtime_error::runtime_error;

        EngineError(const ApiStatusCode errorCode);
        EngineError(const ApiStatusCode errorCode, std::string_view message);

        ApiStatusCode getErrorCode() const;
};

#endif // ERRORS_HPP
