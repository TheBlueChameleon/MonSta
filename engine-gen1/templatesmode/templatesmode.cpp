#include <string>

#include <runmodes/ITemplatesDefinition.hpp>

#include <services/fileservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "shared/schemavalidationconstants.hpp"

#include "templatesmode.hpp"

using namespace std::string_literals;

namespace TemplateMode
{
    static const std::string UNDEFINED = "<to be defined>";

    static std::string quote(const std::string_view quotee)
    {
        return "\""s + quotee.data() + "\"";
    }

    static std::string_view writeMechanicsDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto tagName = SchemaValidation::jtag_base + defaultName.data();
        const auto handle = JsonService::parseValidatePatchAndAdd(
                                IJsonServiceTypes::JsonTag(tagName.data()),
                                "{}",
                                SchemaValidation::JTAG_MECHANICSDEFINITION
                            );
        auto memBlock = JsonService::dump(handle);

        FileService::write(defaultName, memBlock.getAsStringView());

        return defaultName;
    }

    static std::string_view writeTeamDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName,
        const std::string_view playerType
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto tagName = SchemaValidation::jtag_base + defaultName.data();
        const auto explicitFields = "{"s +
                                    quote(playerType) + " : " + "{" + quote(SchemaValidation::JKEY_PLAYER_NAME) + " : " + quote(UNDEFINED) + "}," +
                                    quote(SchemaValidation::JKEY_POKEMON) + ": [{" +
                                    quote(SchemaValidation::JKEY_POKEMON_SPECIES) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_LEVEL) + " : 5," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK1) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK2) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK3) + " : " + quote(UNDEFINED) + "," +
                                    quote(SchemaValidation::JKEY_POKEMON_ATTACK4) + " : " + quote(UNDEFINED) +
                                    "}]" +
                                    "}";

        const auto handle = JsonService::parseValidatePatchAndAdd(
                                IJsonServiceTypes::JsonTag(tagName.data()),
                                explicitFields,
                                SchemaValidation::JTAG_TEAMDEFINITION
                            );
        auto memBlock = JsonService::dump(handle);

        FileService::write(defaultName, memBlock.getAsStringView());

        return defaultName;
    }

    static std::string_view writeStrategyFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto strategy = R"(to be done)";

        FileService::write(defaultName, strategy);

        return defaultName;
    }

    static std::string_view writePkmnDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";

        FileService::write(defaultName, content);

        return defaultName;
    }

    static std::string_view writeMoveDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

    static std::string_view writeTypeDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

    static std::string_view writeItemDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }

        const auto content = R"(to be done)";
        FileService::write(defaultName, content);

        return defaultName;
    }

    static void writeSchemas()
    {
        auto handleTeamDef = JsonService::get(SchemaValidation::JTAG_TEAMDEFINITION);
        auto contentTeamDef = JsonService::dump(handleTeamDef);
        FileService::write(SchemaValidation::filename_teamDefinitionSchema, contentTeamDef.getAsStringView());

        auto handleMechanicsDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
        auto contentMechanicsDef = JsonService::dump(handleMechanicsDef);
        FileService::write(SchemaValidation::filename_mechanicsDefinitionSchema, contentMechanicsDef.getAsStringView());
    }

    static void writeAllowedValueFile()
    {
        const auto content = R"(to be done)";
        FileService::write(ALLOWED_VALUES_FILE, content);
    }

    const ITemplatesDefinition run(const ITemplatesDefinition& templatesDefinition)
    {
        if (templatesDefinition.writeSchemas)
        {
            writeSchemas();
        }

        if (templatesDefinition.writeAllowedValues)
        {
            writeAllowedValueFile();
        }

        const auto mechanicsDefinitionFile = writeMechanicsDefinitionFile(templatesDefinition.mechanicsDefinition, MECHANICS_DEFINITION_FILE);
        const auto player1TeamDefinitionFile = writeTeamDefinitionFile(templatesDefinition.player1Team, PLAYER1_TEAMDEFINITION_FILE, SchemaValidation::JKEY_HUMAN);
        const auto player2TeamDefinitionFile = writeTeamDefinitionFile(templatesDefinition.player2Team, PLAYER2_TEAMDEFINITION_FILE, SchemaValidation::JKEY_COMPUTER);
        const auto player1StrategyFile = writeStrategyFile(templatesDefinition.player1Team, PLAYER1_STRATEGY_FILE);
        const auto player2StrategyFile = writeStrategyFile(templatesDefinition.player2Team, PLAYER2_STRATEGY_FILE);
        const auto pkmnDefinitionFile = writePkmnDefinitionFile(templatesDefinition.pkmnDefs, PKMN_DEFINITION_FILE);
        const auto moveDefinitionFile = writeMoveDefinitionFile(templatesDefinition.moveDefs, MOVE_DEFINITION_FILE);
        const auto typeDefinitionFile = writeTypeDefinitionFile(templatesDefinition.typeDefs, TYPE_DEFINITION_FILE);
        const auto itemDefinitionFile = writeItemDefinitionFile(templatesDefinition.itemDefs, ITEM_DEFINITION_FILE);

        return ITemplatesDefinition
        {
            templatesDefinition.writeSchemas,
            templatesDefinition.writeAllowedValues,
            mechanicsDefinitionFile.data(),
            player1TeamDefinitionFile.data(),
            player2TeamDefinitionFile.data(),
            player1StrategyFile.data(),
            player2StrategyFile.data(),
            pkmnDefinitionFile.data(),
            moveDefinitionFile.data(),
            typeDefinitionFile.data(),
            itemDefinitionFile.data(),
            templatesDefinition.args
        };
    }
}
