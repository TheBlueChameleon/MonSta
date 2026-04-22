#ifndef SETUPERRORHANDLING_HPP
#define SETUPERRORHANDLING_HPP

#include <filesystem>

#include <ApiStatusCode.hpp>

namespace EngineBase
{
    class ErrorBuffer;
}

namespace SimulationMode
{
    [[noreturn]] void abort(
        const std::string_view message,
        const ApiStatusCode errorCode = ApiStatusCode::INVALID_USER_INPUT
    );

    void report(
        EngineBase::ErrorBuffer& eb,
        const std::string_view message,
        const std::filesystem::path& origin
    );

} // namespace SimulationMode

#endif // SETUPERRORHANDLING_HPP
