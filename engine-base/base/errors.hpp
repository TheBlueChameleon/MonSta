#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <stdexcept>

#include <ApiStatusCode.hpp>

// ========================================================================== //
// Base Error

class EngineError : public std::runtime_error
{
    protected:
        int errorCode = ApiStatusCode::ILLEGAL_STATE;

    public:
        using std::runtime_error::runtime_error;

        EngineError(std::string_view message);
        EngineError(const int errorCode, std::string_view message);

        int getErrorCode() const;
};

// ========================================================================== //
// Pre-Coded errors

class InvalidUserInput : EngineError
{
    public:
        using EngineError::EngineError;

        InvalidUserInput();
        InvalidUserInput(const std::string_view msg);
};

class IllegalStateError : EngineError
{
    public:
        using EngineError::EngineError;

        IllegalStateError();
        IllegalStateError(const std::string_view msg);
};

class IllegalArgumentError : EngineError
{
    public:
        using EngineError::EngineError;

        IllegalArgumentError();
        IllegalArgumentError(const std::string_view msg);
};

class MissingParameterError : EngineError
{
    public:
        using EngineError::EngineError;

        MissingParameterError();
        MissingParameterError(const std::string_view msg);
};

class NotImplementedError : EngineError
{
    public:
        using EngineError::EngineError;

        NotImplementedError();
        NotImplementedError(const std::string_view msg);
};

class MultipleErrors : EngineError
{
    public:
        using EngineError::EngineError;

        MultipleErrors();
        MultipleErrors(const std::string_view msg);
};

class LookupError : EngineError
{
    public:
        using EngineError::EngineError;

        LookupError();
        LookupError(const std::string_view msg);
};

// ========================================================================== //
// Aux Functions

namespace EngineBase
{
    void passExceptionToHost(const EngineError& e);
}

#endif // ERRORS_HPP
