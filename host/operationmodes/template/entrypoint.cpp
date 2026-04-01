#include "errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "templatemodedefinition.hpp"

namespace TemplateMode
{
    void run(const TemplateModeDefinition& defs)
    {
        OperationModes::setupLogger(defs.logging);

        LoggerService::info("Template mode not implemented yet.");
        std::exit(0);
    }
}
