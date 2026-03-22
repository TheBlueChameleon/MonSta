#ifndef TEMPLATEMODEDEFINITION_HPP
#define TEMPLATEMODEDEFINITION_HPP

#include "basemodedefinition.hpp"

struct TemplateModeDefinition : public BaseModeDefinition
{
    TemplateModeDefinition(const CliInput& cli):
        BaseModeDefinition(cli, LoggingDefinition())
    {}
};

#endif // TEMPLATEMODEDEFINITION_HPP
