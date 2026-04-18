#include <sstream>
#include <string>

#include "services/jsonservice.hpp"
#include "services/memoryservice.hpp"

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

using namespace std::string_literals;
using namespace IJsonServiceTypes;
using namespace JsonService;

namespace SchemaValidation
{
    // ====================================================================== //
    // Constants

    const std::string jtag_mechanicsDefinition = Globals::jtag_base + filename_mechanicsDefinitionSchema;
    const std::string jtag_teamDefinition      = Globals::jtag_base + filename_teamDefinitionSchema;

    const IJsonServiceTypes::JsonTag JTAG_MECHANICSDEFINITION = JsonTag(jtag_mechanicsDefinition.data());
    const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION      = JsonTag(jtag_teamDefinition.data());

    // ====================================================================== //
    // Helpers

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

    const char* const boolToLiteral(const bool flag)
    {
        return flag ? "true" : "false";
    }

    // ====================================================================== //
    // Mechanics Definition

    void registerMechanicsDefinition()
    {
        auto builder = JsonService::JsonSchemaBuilder("<root>");

        builder
        .addProperty(JKEY_MECHANICS_LEVELCAP, JsonType::INTEGER)
        .setDefault("100");

        builder
        .addProperty(JKEY_MECHANICS_STATSMIN, JsonType::INTEGER)
        .setDefault("0");

        builder
        .addProperty(JKEY_MECHANICS_STATSMAX, JsonType::INTEGER)
        .setDefault("999");

        builder
        .addProperty(JKEY_MECHANICS_OBEDIENCE, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_GEN1MISS, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_BIDE_GLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_COUNTERGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_CRITRATEGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_EXPUNDERFLOWGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_HPRECOVERYGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_INVULNERABILITYGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_JUMPKICKGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_MIMICLEVELUPGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_STATMODGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_SUBSTITUTEHPDRAINGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_SUBSTITUTESELFHURTGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_TOXICRESTGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_TOXICLEECHSEEDGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder.buildAndAdd(JTAG_MECHANICSDEFINITION);
    }

    // ====================================================================== //
    // Team Definition

    static void addBadgeOptions(
        JsonSchemaBuilder& result,
        const bool hasBoostAtk,
        const bool hasBoostDef,
        const bool hasBoostSpc,
        const bool hasBoostSpd
    )
    {
        result
        .addProperty(JKEY_PLAYER_BADGEATK, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(hasBoostAtk));

        result
        .addProperty(JKEY_PLAYER_BADGEDEF, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(hasBoostDef));

        result
        .addProperty(JKEY_PLAYER_BADGESPC, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(hasBoostSpc));

        result
        .addProperty(JKEY_PLAYER_BADGESPD, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(hasBoostSpd));

        result
        .addProperty(JKEY_PLAYER_OBEDIENCECAP, JsonType::INTEGER)
        .setDefault("100");
    }

    static void addMechanicsOptions(
        JsonSchemaBuilder& result,
        const bool hasStatusMoveDebuf,
        const bool doesUsePP
    )
    {
        result
        .addProperty(JKEY_PLAYER_STATUSMOVEDEBUFF, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(hasStatusMoveDebuf));

        result
        .addProperty(JKEY_PLAYER_USEPP, JsonType::BOOLEAN)
        .setDefault(boolToLiteral(doesUsePP));

        result
        .addProperty(JKEY_PLAYER_EXPALL, JsonType::BOOLEAN)
        .setDefault("false");
    }

    static const JsonSchemaBuilder makeHumanSubSchema()
    {
        JsonSchemaBuilder result(JKEY_HUMAN);
        result.addRequired(JKEY_PLAYER_NAME);

        result.addProperty(JKEY_PLAYER_NAME, JsonType::STRING);

        addBadgeOptions(result, true, true,true, true);
        addMechanicsOptions(result, false, true);

        return result;
    }

    static const JsonSchemaBuilder makeComputerSubSchema()
    {
        JsonSchemaBuilder result(JKEY_COMPUTER);
        result.addRequired(JKEY_PLAYER_NAME);

        result.addProperty(JKEY_PLAYER_NAME, JsonType::STRING);

        addBadgeOptions(result, false, false, false, false);
        addMechanicsOptions(result, true, false);

        return result;
    }

    static const JsonSchemaBuilder makePokemonSubSchema()
    {
        JsonSchemaBuilder result(JKEY_POKEMON);

        result.addRequired(JKEY_POKEMON_SPECIES);
        result.addRequired(JKEY_POKEMON_LEVEL);
        result.addRequired(JKEY_POKEMON_ATTACK1);

        result.addProperty(JKEY_POKEMON_SPECIES, JsonType::STRING);
        result.addProperty(JKEY_POKEMON_LEVEL, JsonType::INTEGER);

        result.addProperty(JKEY_POKEMON_HPCURRENT, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");

        result.addProperty(JKEY_POKEMON_EXP, JsonType::INTEGER)
        .setDefault("-1");

        result.addProperty(JKEY_POKEMON_FOREIGN, JsonType::BOOLEAN)
        .setDefault("false");

        result.addProperty(JKEY_POKEMON_STATUS)
        .setEnum(makeJsonList({JKEY_POKEMON_STATUS_NORMAL,
                               JKEY_POKEMON_STATUS_PARALYZED,
                               JKEY_POKEMON_STATUS_POISONED,
                               JKEY_POKEMON_STATUS_ASLEEP,
                               JKEY_POKEMON_STATUS_BURNT,
                               JKEY_POKEMON_STATUS_FROZEN,
                               JKEY_POKEMON_STATUS_FAINTED
                              }))
        .setDefault("\""s + JKEY_POKEMON_STATUS_NORMAL + "\"");

        result.addProperty(JKEY_POKEMON_DVHP, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_DVATK, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_DVDEF, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_DVSPC, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_DVSPD, JsonType::INTEGER)
        .setDefault("-1")
        .setMinimum("-1");

        result.addProperty(JKEY_POKEMON_STATEXPHP, JsonType::INTEGER)
        .setDefault("0")
        .setMinimum("0");
        result.addProperty(JKEY_POKEMON_STATEXPATK, JsonType::INTEGER)
        .setDefault("0")
        .setMinimum("0");
        result.addProperty(JKEY_POKEMON_STATEXPDEF, JsonType::INTEGER)
        .setDefault("0")
        .setMinimum("0");
        result.addProperty(JKEY_POKEMON_STATEXPSPC, JsonType::INTEGER)
        .setDefault("0")
        .setMinimum("0");
        result.addProperty(JKEY_POKEMON_STATEXPSPD, JsonType::INTEGER)
        .setDefault("0")
        .setMinimum("0");

        result.addProperty(JKEY_POKEMON_ATTACK1, JsonType::STRING);
        result.addProperty(JKEY_POKEMON_ATTACK1PP, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_ATTACK1PPCURRENT, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");

        result.addProperty(JKEY_POKEMON_ATTACK2, JsonType::STRING);
        result.addProperty(JKEY_POKEMON_ATTACK2PP, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_ATTACK2PPCURRENT, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");

        result.addProperty(JKEY_POKEMON_ATTACK3, JsonType::STRING);
        result.addProperty(JKEY_POKEMON_ATTACK3PP, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_ATTACK3PPCURRENT, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");

        result.addProperty(JKEY_POKEMON_ATTACK4, JsonType::STRING);
        result.addProperty(JKEY_POKEMON_ATTACK4PP, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");
        result.addProperty(JKEY_POKEMON_ATTACK4PPCURRENT, JsonType::STRING)
        .setDefault("-1")
        .setMinimum("-1");

        return result;
    }

    void registerSchemaTeamDefinition()
    {
        auto builder = JsonService::JsonSchemaBuilder("<root>");

        builder.addOneOfRequirement(makeRequiredBlock({JKEY_HUMAN}));
        builder.addOneOfRequirement(makeRequiredBlock({JKEY_COMPUTER}));
        builder.addRequired(JKEY_POKEMON);

        builder
        .addProperty(JKEY_POKEMON, JsonType::ARRAY)
        .setProperty("items", R"({"$ref": "#/$defs/)"s + JKEY_POKEMON + "\"}")
        .setProperty("minItems", "1");

        builder.addReference(JKEY_HUMAN, makeHumanSubSchema(), JsonType::OBJECT, false);
        builder.addReference(JKEY_COMPUTER, makeComputerSubSchema(), JsonType::OBJECT, false);
        builder.addSubSchema(makePokemonSubSchema());

        builder.buildAndAdd(JTAG_TEAMDEFINITION);
    }
}
