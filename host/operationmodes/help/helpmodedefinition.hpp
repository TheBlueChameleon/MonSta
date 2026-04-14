#ifndef HELPMODEDEFINITION_HPP
#define HELPMODEDEFINITION_HPP

#include "cli/cliinput.hpp"

#include "operationmodes/shared/basemodedefinition.hpp"

namespace OperationModes
{
    struct HelpModeDefinition : public BaseModeDefinition
    {
        HelpModeDefinition(
            const CliInput& cli,
            OperationMode target
        ):
            BaseModeDefinition(cli, LoggingDefinition()),
            target(target)
        {}

        OperationMode target;
    };
}

#endif // HELPMODEDEFINITION_HPP
