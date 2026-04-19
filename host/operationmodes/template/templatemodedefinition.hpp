#ifndef TEMPLATEMODEDEFINITION_HPP
#define TEMPLATEMODEDEFINITION_HPP

#include "operationmodes/shared/basemodedefinition.hpp"

#include "defs/templatesdefinition.hpp"

namespace OperationModes
{
    struct TemplateModeDefinition : public BaseModeDefinition
    {
        TemplateModeDefinition(
            const CliInput& cli,
            const LoggingDefinition& logging,
            const PathsDefinition& paths,
            const TemplatesDefinition templates
        ):
            BaseModeDefinition(cli, logging, paths),
            templates(templates)
        {}

        TemplatesDefinition templates;
    };
}

#endif // TEMPLATEMODEDEFINITION_HPP
