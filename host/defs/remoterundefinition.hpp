#ifndef REMOTERUNDEFINITION_HPP
#define REMOTERUNDEFINITION_HPP

#include "basemodedefinition.hpp"

struct RemoteModeDefinition : public BaseModeDefinition
{
    RemoteModeDefinition():
        BaseModeDefinition(OperationMode::REMOTE, LoggingDefinition())
    {}
};

#endif // REMOTERUNDEFINITION_HPP
