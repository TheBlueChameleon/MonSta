#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/safecast.hpp"

#include "entrypoint.hpp"
#include "templatemodedefinition.hpp"

void TemplateMode::run(const std::shared_ptr<const BaseModeDefinition>& defs)
{
    const TemplateModeDefinition& xDefs = RunDefinitionUtils::getAsTemplateModeDefinition(defs);
    LoggerService::setup(xDefs.logging);

    LoggerService::info("Template mode not implemented yet.");
    std::exit(0);
}
