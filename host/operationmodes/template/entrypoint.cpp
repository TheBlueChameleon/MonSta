#include "api/clientwrapper.hpp"

#include "errorservice/errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "templatemodedefinition.hpp"

namespace TemplateMode
{
    void run(const OperationModes::TemplateModeDefinition& defs)
    {
        OperationModes::setupLoggerService(defs.logging);
        OperationModes::setupFileService(defs, defs.templates.outputDirectory);

        auto cw = ClientWrapper(defs.templates.engine);
        OperationModes::setupClientWriteOptions(cw, defs);

        cw.startTemplatesMode();
    }
}
