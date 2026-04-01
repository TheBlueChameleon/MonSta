#include "errors.hpp"

#include "fileservice/fileservice.hpp"

//#include "json/schemaconstants.hpp"

#include "jsonservice/jsonservicedatabase.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/schemavalidation.hpp"
#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "schemaexportmodedefinition.hpp"

namespace SchemaExportMode
{
    void run(const SchemaExportModeDefinition& defs)
    {
        OperationModes::setupLoggerService(defs.logging);                       // apply defaults
        OperationModes::setupFileService(defs, defs.outputDirectory);

        // TODO: remove bypass through Database
        auto& instance = JsonService::JsonServiceDatabase::getInstance();
        auto& sim = instance.get(JTAG_SIMULATION);
        auto& tpl = instance.get(JTAG_TEMPLATE);

        LoggerService::trace("begin writing schemas");
        FileService::write("simulation.json", sim.dump(2));
        FileService::write("template.json", tpl.dump(2));

        if (!defs.dryMode)
        {
            LoggerService::infoF(
                "schemas written into '{}'",
                std::filesystem::weakly_canonical(defs.outputDirectory).c_str()
            );
        }
    }
}

