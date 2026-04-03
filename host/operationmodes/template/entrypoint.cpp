#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "api/clientwrapper.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "templatemodedefinition.hpp"

namespace TemplateMode
{
    void run(const TemplateModeDefinition& defs)
    {
        OperationModes::setupLoggerService(defs.logging);
        OperationModes::setupFileService(defs, defs.templates.outputDirectory);

        auto cw = ClientWrapper(defs.templates.engine);

        LoggerService::info("Template mode not implemented yet.");
        std::exit(0);
    }
}
