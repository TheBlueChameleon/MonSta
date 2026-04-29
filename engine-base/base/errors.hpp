#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

#include <ApiStatusCode.hpp>

class EngineError : public std::runtime_error
{
    protected:
        int errorCode = ApiStatusCode::ILLEGAL_CLIENT_STATE;

    public:
        using std::runtime_error::runtime_error;

        EngineError(const int errorCode);
        EngineError(const int errorCode, std::string_view message);

        int getErrorCode() const;
};

namespace EngineBase
{
    void passExceptionToHost(const EngineError& e);
}

#endif // ERRORS_HPP
