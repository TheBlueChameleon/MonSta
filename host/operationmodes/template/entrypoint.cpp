#include <runmodes/ITemplatesDefinition.hpp>

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

        ITemplatesDefinition td =
        {
            defs.templates.engine.c_str(),
            defs.templates.outputDirectory.c_str(),
            defs.templates.player1Team.c_str(),
            defs.templates.player1Strategy.c_str(),
            defs.templates.player2Team.c_str(),
            defs.templates.player2Strategy.c_str(),
            defs.templates.pkmnDefs.c_str(),
            defs.templates.moveDefs.c_str(),
            defs.templates.typeDefs.c_str(),
            defs.templates.itemDefs.c_str(),
            defs.templates.args.data(),
            defs.templates.writeSchemas
        };

        cw.startTemplatesMode(td);
    }
}
