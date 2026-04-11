#include <iostream>

#include "services/jsonservice.hpp"
#include "services/memoryservice.hpp"

#include "schemavalidationconstants.hpp"

using namespace IJsonServiceTypes;

namespace SchemaValidation
{
    const IJsonServiceTypes::JsonTag JTAG_BASE              = JsonTag(":storage:/gen1/");
    const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION    = JsonTag(":storage:/gen1/teamDefinition.json");

    void registerTeamDefinition()
    {
        auto tag = IJsonServiceTypes::JsonTag("tag");
        auto sb = JsonService::instantiateSchemaBuilder("foo");

        auto h = JsonService::sb_buildAndAdd(sb, tag);

        auto j = JsonService::get(tag);

        auto s = JsonService::dump(j);

        std::cout << s.getAsStringView() << std::endl;
    }
}
