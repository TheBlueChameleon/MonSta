#include "../../errors.hpp"

#include "../../fileservice/fileservice.hpp"

#include "../../json/schemaconstants.hpp"

#include "../../logging/loggerservice.hpp"

#include "../safecast.hpp"

#include "entrypoint.hpp"
#include "schemaexportmodedefinition.hpp"

namespace SchemaExportMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const SchemaExportModeDefinition xDefs = RunDefinitionUtils::getAsSchemaExportModeDefinition(defs);

        FileService::setBase(xDefs.outputDirectory);
        FileService::setOverwrite(xDefs.overwrite);
        FileService::setCreateDirectories(xDefs.createDirectories);
        FileService::setDryMode(xDefs.dryMode);

        FileService::write("simulation.json", SCHEMA_SIMULATION_STRING);
        FileService::write("template.json", SCHEMA_TEMPLATE_STRING);

        if (!xDefs.dryMode)
        {
            LoggerService::infoF(
                "schemas written into '{}'",
                std::filesystem::canonical(xDefs.outputDirectory).c_str()
            );
        }
    }
}

