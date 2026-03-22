#include "../api/loggerservice.hpp"

#include "../defs/safecast.hpp"

#include "../filewriter/filewriterservice.hpp"

#include "../json/schemaconstants.hpp"

#include "../errors.hpp"

#include "entrypoint.hpp"

namespace SchemaExportMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const SchemaExportModeDefinition xDefs = RunDefinitionUtils::getAsSchemaExportModeDefinition(defs);

        FileWriterService::setBase(xDefs.outputDirectory);

        FileWriterService::write("simulation.json", SCHEMA_SIMULATION_STRING);
        FileWriterService::write("template.json", SCHEMA_TEMPLATE_STRING);

        LoggerService::infoF("schemas written into '{}'", xDefs.outputDirectory.c_str());
    }
}

