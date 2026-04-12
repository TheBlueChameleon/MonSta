#include <iostream>
#include <sstream>
#include <string>

#include "services/jsonservice.hpp"
#include "services/memoryservice.hpp"

#include "schemavalidationconstants.hpp"

using namespace IJsonServiceTypes;
using namespace JsonService;

namespace SchemaValidation
{
    const IJsonServiceTypes::JsonTag JTAG_BASE           = JsonTag(":storage:/gen1/");
    const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION = JsonTag(":storage:/gen1/teamDefinition.json");

    static const std::string makeJsonList(std::initializer_list<const char* const> items)
    {
        const auto N = items.size();
        std::stringstream buffer;
        buffer << "[";

        for (int i = 0; auto item : items)
        {
            ++i;
            buffer << "\"" << item << "\"";
            if (i < N)
            {
                buffer << ", ";
            }
        }

        buffer << "]";
        return buffer.str();
    }

    static const std::string makeRequiredBlock(std::initializer_list<const char* const> items)
    {
        std::stringstream buffer;
        buffer << "{ \"required\": " << makeJsonList(items) << " }";
        return buffer.str();
    }

    static const JsonSchemaBuilder makeHumanSubSchema()
    {
        JsonSchemaBuilder result(JKEY_HUMAN);

        result
        .addProperty(JKEY_PLAYER_BADGES)
        .setEnumArray(makeJsonList(
        {
            JKEY_PLAYER_BADGES_BROCK,
            JKEY_PLAYER_BADGES_MISTY,
            JKEY_PLAYER_BADGES_SURGE,
            JKEY_PLAYER_BADGES_ERIKA,
            JKEY_PLAYER_BADGES_SABRINA,
            JKEY_PLAYER_BADGES_KOGA,
            JKEY_PLAYER_BADGES_BLAINE,
            JKEY_PLAYER_BADGES_GIOVANNI
        }));
        return result;
    }

    static const JsonSchemaBuilder makeComputerSubSchema()
    {
        JsonSchemaBuilder result(JKEY_COMPUTER);
        return result;
    }

    static const JsonSchemaBuilder makePokemonSubSchema()
    {
        JsonSchemaBuilder result(JKEY_POKEMON);
        return result;
    }

    void registerSchemaTeamDefinition()
    {
        auto builder = JsonService::JsonSchemaBuilder("<root>");

        builder.addOneOfRequirement(makeRequiredBlock({JKEY_HUMAN}));
        builder.addOneOfRequirement(makeRequiredBlock({JKEY_COMPUTER}));
        builder.addRequired(JKEY_POKEMON);

        builder.addProperty(JKEY_POKEMON, JsonType::ARRAY).setReference(JKEY_POKEMON);

        builder.addReference(JKEY_HUMAN, makeHumanSubSchema());
        builder.addReference(JKEY_COMPUTER, makeComputerSubSchema());
        builder.addSubSchema(makePokemonSubSchema());

        auto handle = builder.buildAndAdd(JTAG_TEAMDEFINITION);

        auto s = JsonService::dump(handle);

        std::cout << s.getAsStringView() << std::endl;
    }
}
