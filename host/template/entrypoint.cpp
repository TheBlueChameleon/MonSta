#include "../api/loggerservice.hpp"

#include "../defs/safecast.hpp"

#include "../errors.hpp"

#include "entrypoint.hpp"

void TemplateMode::run(const std::shared_ptr<const BaseModeDefinition>& defs)
{
    const TemplateModeDefinition& xDefs = RunDefinitionUtils::getAsTemplateModeDefinition(defs);
    LoggerService::setup(xDefs.logging);

    LoggerService::info("Template mode not implemented yet.");
    std::exit(0);
}
