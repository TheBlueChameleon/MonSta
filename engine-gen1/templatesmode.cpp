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
        FileService::write(SchemaValidation::FILENAME_TEAMDEFINITION, content.getAsStringView());

        auto handleXDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
        auto contentX = JsonService::dump(handleXDef);
        FileService::write(SchemaValidation::FILENAME_MECHANICSDEFINITION, contentX.getAsStringView());
    }

    void run(const ITemplatesDefinition& templatesDefinition)
    {
        if (templatesDefinition.writeSchemas)
        {
            writeSchemas();
        }
    }
}
