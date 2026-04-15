#include <runmodes/ITemplatesDefinition.hpp>

#include "services/fileservice.hpp"
#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

#include "schemavalidationconstants.hpp"
#include "templatesmode.hpp"

namespace TemplateMode
{
    void writeSchemas()
    {
        auto handleTeamDef = JsonService::get(SchemaValidation::JTAG_TEAMDEFINITION);
        auto content = JsonService::dump(handleTeamDef);
        FileService::write(SchemaValidation::filename_teamDefinition, content.getAsStringView());

        auto handleXDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
        auto contentX = JsonService::dump(handleXDef);
        FileService::write(SchemaValidation::filename_mechanicsDefinition, contentX.getAsStringView());
    }

    void run(const ITemplatesDefinition& templatesDefinition)
    {
        if (templatesDefinition.writeSchemas)
        {
            writeSchemas();
        }
    }
}
