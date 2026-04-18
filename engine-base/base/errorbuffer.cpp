#include <sstream>

#include "errorbuffer.hpp"

namespace EngineBase
{
    // ====================================================================== //
    // ErrorData

    ErrorBuffer::ErrorData::ErrorData(ApiStatusCode errorCode, std::string errorMessage) :
        errorCode(errorCode), errorMessage(errorMessage)
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

    void ErrorBuffer::append(ApiStatusCode errorCode, const std::string_view errorMessage)
    {
        errors.emplace_back(errorCode, errorMessage.data());
    }

    void ErrorBuffer::append(const EngineError& error)
    {
        append(error.getErrorCode(), error.what());
    }

    void ErrorBuffer::append(const std::exception& error)
    {
        append(ApiStatusCode::CRITICAL_ABORT, error.what());
    }

} // namespace EngineBase
