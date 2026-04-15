#include <nlohmann/json.hpp>

#include "errorservice/errors.hpp"

#include "fileservice/fileservice.hpp"

#include "jsonservice/jsonservice.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/schemavalidationconstants.hpp"
#include "operationmodes/shared/utils.hpp"

#include "schemaexportmodeimplementation.hpp"
#include "schemaexportmodedefinition.hpp"

namespace OperationModes
{
    void runSchemaExportMode(const SchemaExportModeDefinition& defs)
    {
        setupLoggerService(defs.logging);
        setupFileService(defs, defs.outputDirectory);

        auto& sim = JsonService::get(JTAG_SIMULATION);
        auto& tpl = JsonService::get(JTAG_TEMPLATES);

        LoggerService::trace("begin writing schemas");
        FileService::write("simulation.json", sim.dump(2));
        FileService::write("templates.json", tpl.dump(2));

        if (!defs.dryMode)
        {
            LoggerService::infoF(
                "schemas written into '{}'",
                std::filesystem::weakly_canonical(defs.outputDirectory).c_str()
            );
        }
    }
}

