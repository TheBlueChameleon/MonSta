#include "errorservice/errors.hpp"

#include "operationmode.hpp"

using namespace std::string_view_literals;

namespace OperationModes
{
    OperationMode getOperationModeFromString(const std::string_view modeString)
    {
    // *INDENT-OFF*
    if (modeString == OperationModes::SIMULATION  ) return OperationMode::SIMULATION;
    if (modeString == OperationModes::TEMPLATES   ) return OperationMode::TEMPLATES;
    if (modeString == OperationModes::SCHEMAEXPORT) return OperationMode::SCHEMAEXPORT;
    if (modeString == OperationModes::REMOTE      ) return OperationMode::REMOTE;
    if (modeString == OperationModes::HELP        ) return OperationMode::HELP;
    // *INDENT-ON*

        throw IllegalHostStateException("Invalid mode identifier: '"s + modeString.data() + "'");
    }


}
