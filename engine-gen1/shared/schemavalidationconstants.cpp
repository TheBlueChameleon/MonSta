#include <format>
#include <sstream>
#include <string>

#include "services/jsonservice.hpp"
#include "services/memoryservice.hpp"

#include "shared/defs/statuscondition.hpp"

#include "schemavalidationconstants.hpp"

using namespace std::string_literals;
using namespace MetaDefinition;
using namespace IJsonServiceTypes;
using namespace JsonService;

namespace SchemaValidation
{
    // ====================================================================== //
    // Constants

    const std::string jtag_base = ":storage:/gen1/";
    const std::string jtag_mechanicsDefinition = jtag_base + filename_mechanicsDefinitionSchema;
    const std::string jtag_teamDefinition      = jtag_base + filename_teamDefinitionSchema;

    const IJsonServiceTypes::JsonTag JTAG_MECHANICSDEFINITION = JsonTag(jtag_mechanicsDefinition.data());
    const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION      = JsonTag(jtag_teamDefinition.data());

    // ====================================================================== //
    // Helpers

    static const std::string makeJsonList(std::initializer_list<const char* const> items)
    {
        const auto N = items.size();
        int i = 0;
        std::stringstream buffer;
        buffer << "[";

        for (auto item : items)
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
        return std::format("{{ \"required\": {} }}", makeJsonList(items));
    }

    static const std::string makeArrayItemsBlock(const std::string_view key, const std::string_view value)
    {
        return std::format(
                   "{{ "
                   R"("type"  : "array", )"
                   R"("items" : {{ "{}" : "{}" }})"
                   " }}",
                   key, value
               );
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
        .addProperty(JKEY_MECHANICS_TEAMSIZEMAX, JsonType::INTEGER)
        .setDefault("6");

        builder
        .addProperty(JKEY_MECHANICS_DVCAP, JsonType::INTEGER)
        .setDefault("15");

        builder
        .addProperty(JKEY_MECHANICS_DVSUMCAP, JsonType::INTEGER)
        .setDefault("75");      // 5*15

        builder
        .addProperty(JKEY_MECHANICS_STATEXPCAP, JsonType::INTEGER)
        .setDefault("65535");

        builder
        .addProperty(JKEY_MECHANICS_STATEXPSUMCAP, JsonType::INTEGER)
        .setDefault("327675");   // 5*65535

        builder
        .addProperty(JKEY_MECHANICS_OBEDIENCECAP, JsonType::INTEGER)
        .setDefault("100");

        builder
        .addProperty(JKEY_MECHANICS_STATSTAGEABSMAX, JsonType::INTEGER)
        .setDefault("6");

        builder
        .addProperty(JKEY_MECHANICS_SLEEPMINTURNS, JsonType::INTEGER)
        .setDefault("2");

        builder
        .addProperty(JKEY_MECHANICS_SLEEPMAXTURNS, JsonType::INTEGER)
        .setDefault("7");

        builder
        .addProperty(JKEY_MECHANICS_FULLPARALYSISCHANCE, JsonType::FLOAT)
        .setDefault("25");

        builder
        .addProperty(JKEY_MECHANICS_CONFUSIONMINTURNS, JsonType::INTEGER)
        .setDefault("2");

        builder
        .addProperty(JKEY_MECHANICS_CONFUSIONMAXTURNS, JsonType::INTEGER)
        .setDefault("5");

        builder
        .addProperty(JKEY_MECHANICS_CONFUSIONHITCHANCE, JsonType::FLOAT)
        .setDefault("50");

        builder
        .addProperty(JKEY_MECHANICS_CONFUSIONHITSTRENGTH, JsonType::INTEGER)
        .setDefault("40");

        builder
        .addProperty(JKEY_MECHANICS_BURNDAMAGEPERCENTAGE, JsonType::FLOAT)
        .setDefault("6.25");

        builder
        .addProperty(JKEY_MECHANICS_POISONDAMAGEPERCENTAGE, JsonType::FLOAT)
        .setDefault("6.25");

        builder
        .addProperty(JKEY_MECHANICS_TOXICCOUNTERMAX, JsonType::INTEGER)
        .setDefault("15");

        builder
        .addProperty(JKEY_MECHANICS_LEECHSEEDPERCENTAGE, JsonType::FLOAT)
        .setDefault("6.25");

        // .................................................................. //
        // glitch flags;

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
        .addProperty(JKEY_MECHANICS_MIMICLEVELUPGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder
        .addProperty(JKEY_MECHANICS_BADGEBOOSTGLITCH, JsonType::BOOLEAN)
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

        builder
        .addProperty(JKEY_MECHANICS_OPPONENTFAINTSKIPGLITCH, JsonType::BOOLEAN)
        .setDefault("true");

        builder.buildAndAdd(JTAG_MECHANICSDEFINITION);
    }

    // ====================================================================== //
    // Team Definition

    static void addBasicOptions(JsonSchemaBuilder& result)
    {
        result.addProperty(JKEY_PLAYER_NAME, JsonType::STRING);
        result.addProperty(JKEY_PLAYER_ITEMS, JsonType::ARRAY)
        .setReference(JKEY_PLAYER_ITEMS)
        .setDefault("[]");
    }

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

        addBasicOptions(result);
        addBadgeOptions(result, true, true,true, true);
        addMechanicsOptions(result, false, true);

        return result;
    }

    static const JsonSchemaBuilder makeComputerSubSchema()
    {
        JsonSchemaBuilder result(JKEY_COMPUTER);
        result.addRequired(JKEY_PLAYER_NAME);

        addBasicOptions(result);
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
        .setEnum(makeJsonList({MetaDefinition::POKEMON_STATUS_NORMAL,
                               MetaDefinition::POKEMON_STATUS_PARALYZED,
                               MetaDefinition::POKEMON_STATUS_POISONED,
                               MetaDefinition::POKEMON_STATUS_ASLEEP,
                               MetaDefinition::POKEMON_STATUS_BURNT,
                               MetaDefinition::POKEMON_STATUS_FROZEN,
                               MetaDefinition::POKEMON_STATUS_FAINTED
                              }))
        .setDefault("\""s + POKEMON_STATUS_NORMAL + "\"");

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

    static const JsonSchemaBuilder makeItemsSchema()
    {
        JsonSchemaBuilder result(JKEY_PLAYER_ITEMS);

        result.addAnyOfRequirement(makeArrayItemsBlock("type", "string"));
        result.addAnyOfRequirement(makeArrayItemsBlock("$ref", "#/$defs/"s + JKEY_ITEM));

        return result;
    }

    static const JsonSchemaBuilder makeItemSchema()
    {
        JsonSchemaBuilder result(JKEY_ITEM);
        result.addRequired(JKEY_PLAYER_ITEMS_NAME);
        result.addRequired(JKEY_PLAYER_ITEMS_QUANTITY);

        result.addProperty(JKEY_PLAYER_ITEMS_NAME, JsonType::STRING);
        result.addProperty(JKEY_PLAYER_ITEMS_QUANTITY, JsonType::INTEGER)
        .setMinimum("1");

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
        builder.addSubSchema(makeItemsSchema());
        builder.addSubSchema(makeItemSchema());

        builder.buildAndAdd(JTAG_TEAMDEFINITION);
    }
}
