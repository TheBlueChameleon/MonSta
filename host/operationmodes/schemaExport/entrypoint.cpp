#include "errors.hpp"

#include "fileservice/fileservice.hpp"

#include "json/schemaconstants.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "schemaexportmodedefinition.hpp"

namespace SchemaExportMode
{
    void run(const SchemaExportModeDefinition& defs)
    {
        OperationModes::setupLoggerService(defs.logging);                       // apply defaults
        OperationModes::setupFileService(defs, defs.outputDirectory);

        LoggerService::trace("begin writing schemas");
        FileService::write("simulation.json", SCHEMA_SIMULATION_STRING);
        FileService::write("template.json", SCHEMA_TEMPLATE_STRING);

        if (!defs.dryMode)
        {
            LoggerService::infoF(
                "schemas written into '{}'",
                std::filesystem::weakly_canonical(defs.outputDirectory).c_str()
            );
        }
    }
}

