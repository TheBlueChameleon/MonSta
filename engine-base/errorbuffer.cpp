#include <sstream>

#include "errorbuffer.hpp"

namespace EngineBase
{
    // ====================================================================== //
    // ErrorData

    ErrorBuffer::ErrorData::ErrorData(ApiStatusCode errorCode, std::string errorMessage) :
        errorCode(errorCode), errorMessage(errorMessage)
    {}

    ErrorBuffer::ErrorData::ErrorData(const EngineError& error) :
        errorCode(error.getErrorCode()), errorMessage(error.what())
    {}

    ErrorBuffer::ErrorData::ErrorData(const std::exception& error) :
        errorCode(ApiStatusCode::CRITICAL_ABORT), errorMessage(error.what())
    {}

    // ====================================================================== //
    // ErrorBuffer

    const std::list<ErrorBuffer::ErrorData>& ErrorBuffer::getErrors() const
    {
        return errors;
    }

    bool ErrorBuffer::isClean() const
    {
        return errors.empty();
    }

    std::string ErrorBuffer::compileErrorMessage() const
    {
        if (isClean())
        {
            return "-- no errors --";
        }

        std::stringstream buffer;

        buffer << "ErrNo." << "\t" << "Description" << "\n";
        for (const auto& error : errors)
        {
            buffer << std::to_string(static_cast<int>(error.errorCode)) << "\t";
            buffer << error.errorMessage << "\n";
        }

        return buffer.str();
    }

} // namespace EngineBase
