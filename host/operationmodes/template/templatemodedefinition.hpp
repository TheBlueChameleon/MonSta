#ifndef TEMPLATEMODEDEFINITION_HPP
#define TEMPLATEMODEDEFINITION_HPP

#include "operationmodes/shared/basemodedefinition.hpp"

struct TemplateModeDefinition : public BaseModeDefinition
{
    TemplateModeDefinition(const CliInput& cli):
        BaseModeDefinition(cli, LoggingDefinition())
    {}
};

#endif // TEMPLATEMODEDEFINITION_HPP
