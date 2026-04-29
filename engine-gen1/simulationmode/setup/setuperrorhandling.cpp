#include <filesystem>
#include <string>

#include <base/errors.hpp>
#include <base/errorbuffer.hpp>

using namespace EngineBase;
using namespace std::string_literals;

namespace SimulationMode
{
    [[noreturn]] void abort(
        const std::string_view message,
        const int errorCode
    )
    {
        throw EngineError(errorCode, message.data());
    }

    void report(
        ErrorBuffer& eb,
        const std::string_view message,
        const std::filesystem::path& origin
    )
    {
        eb.append(
            ApiStatusCode::INVALID_USER_INPUT,
            "In team definition file '"s + origin.c_str() + "' " + message.data()
        );
    }
} // namespace SimulationMode
