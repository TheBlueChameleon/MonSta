#ifndef TEMPLATEMODEDEFINITION_HPP
#define TEMPLATEMODEDEFINITION_HPP

#include "operationmodes/shared/basemodedefinition.hpp"

#include "defs/templatesdefinition.hpp"

struct TemplateModeDefinition : public BaseModeDefinition
{
    TemplateModeDefinition(
        const CliInput& cli,
        const LoggingDefinition& logging,
        const TemplatesDefinition templates
    ):
        BaseModeDefinition(cli, logging),
        templates(templates)
    {}

    TemplatesDefinition templates;
};

#endif // TEMPLATEMODEDEFINITION_HPP
