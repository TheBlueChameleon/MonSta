#include "../api/loggerservice.hpp"

#include "../defs/safecast.hpp"

#include "../errors.hpp"

#include "entrypoint.hpp"

namespace SchemaExportMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const SchemaExportModeDefinition xDefs = RunDefinitionUtils::getAsSchemaExportModeDefinition(defs);

        LoggerService::info("SCHEMING");
    }
}

