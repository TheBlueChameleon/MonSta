#ifndef REMOTERUNDEFINITION_HPP
#define REMOTERUNDEFINITION_HPP

#include "cli/cliinput.hpp"

#include "operationmodes/shared/basemodedefinition.hpp"

namespace OperationModes
{
    struct RemoteModeDefinition : public BaseModeDefinition
    {
        RemoteModeDefinition(const CliInput& cli):
            BaseModeDefinition(cli, LoggingDefinition(), PathsDefinition())
        {}
    };
}

#endif // REMOTERUNDEFINITION_HPP
