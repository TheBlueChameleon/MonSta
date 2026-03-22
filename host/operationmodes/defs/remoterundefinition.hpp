#ifndef REMOTERUNDEFINITION_HPP
#define REMOTERUNDEFINITION_HPP

#include "../../cli/cliinput.hpp"

#include "basemodedefinition.hpp"

struct RemoteModeDefinition : public BaseModeDefinition
{
    RemoteModeDefinition(const CliInput& cli):
        BaseModeDefinition(cli, LoggingDefinition())
    {}
};

#endif // REMOTERUNDEFINITION_HPP
