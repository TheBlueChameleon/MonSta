#ifndef OPERATIONMODE_HPP
#define OPERATIONMODE_HPP

#include <string_view>

namespace OperationModes
{
    static constexpr auto SIMULATION   = "SIMULATION";
    static constexpr auto TEMPLATES    = "TEMPLATES";
    static constexpr auto SCHEMAEXPORT = "SCHEMAEXPORT";
    static constexpr auto REMOTE       = "REMOTE";
    static constexpr auto HELP         = "HELP";

    enum class OperationMode
    {
        SIMULATION, TEMPLATES, SCHEMAEXPORT, REMOTE, HELP
    };

    OperationMode getOperationModeFromString(const std::string_view modeString);
}

#endif // OPERATIONMODE_HPP
