#include "../../errors.hpp"

#include "../../filewriter/filewriterservice.hpp"

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

        FileWriterService::setBase(xDefs.outputDirectory);
        FileWriterService::setOverwrite(xDefs.overwrite);
        FileWriterService::setCreateDirectories(xDefs.createDirectories);
        FileWriterService::setDryMode(xDefs.dryMode);

        FileWriterService::write("simulation.json", SCHEMA_SIMULATION_STRING);
        FileWriterService::write("template.json", SCHEMA_TEMPLATE_STRING);

        if (!xDefs.dryMode)
        {
            LoggerService::infoF(
                "schemas written into '{}'",
                std::filesystem::canonical(xDefs.outputDirectory).c_str()
            );
        }
    }
}

