#ifndef HELPMODEDEFINITION_HPP
#define HELPMODEDEFINITION_HPP

#include "basemodedefinition.hpp"

struct HelpModeDefinition : public BaseModeDefinition
{
    HelpModeDefinition(OperationMode target):
        BaseModeDefinition(OperationMode::HELP, LoggingDefinition()),
        target(target)
    {}

    OperationMode target;
};

#endif // HELPMODEDEFINITION_HPP
