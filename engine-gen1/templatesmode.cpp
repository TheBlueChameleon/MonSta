#include <runmodes/ITemplatesDefinition.hpp>

#include "services/fileservice.hpp"
#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

#include "schemavalidationconstants.hpp"
#include "templatesmode.hpp"

namespace TemplateMode
{
    static std::string_view writeMechanicsDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string_view writeTeamDefinitionFile(
        const std::string_view inputName,
        const std::string_view defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


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


        return defaultName;
    }

    static void writeSchemas()
    {
        auto handleTeamDef = JsonService::get(SchemaValidation::JTAG_TEAMDEFINITION);
        auto contentTeamDef = JsonService::dump(handleTeamDef);
        FileService::write(SchemaValidation::filename_teamDefinition, contentTeamDef.getAsStringView());

        auto handleMechanicsDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
        auto contentMechanicsDef = JsonService::dump(handleMechanicsDef);
        FileService::write(SchemaValidation::filename_mechanicsDefinition, contentMechanicsDef.getAsStringView());
    }

    static void writeAllowedValueFile()
    {

    }

    const ITemplatesDefinition run(const ITemplatesDefinition& templatesDefinition)
    {
        const auto mechanicsDefinitionFile = writeMechanicsDefinitionFile(templatesDefinition.mechanicsDefinition, MECHANICS_DEFINITION_FILE);
        const auto player1TeamDefinitionFile = writeTeamDefinitionFile(templatesDefinition.player1Team, PLAYER1_TEAMDEFINITION_FILE);
        const auto player2TeamDefinitionFile = writeTeamDefinitionFile(templatesDefinition.player2Team, PLAYER2_TEAMDEFINITION_FILE);
        const auto player1StrategyFile = writeTeamDefinitionFile(templatesDefinition.player1Team, PLAYER1_STRATEGY_FILE);
        const auto player2StrategyFile = writeTeamDefinitionFile(templatesDefinition.player2Team, PLAYER2_STRATEGY_FILE);
        const auto pkmnDefinitionFile = writePkmnDefinitionFile(templatesDefinition.pkmnDefs, PKMN_DEFINITION_FILE);
        const auto moveDefinitionFile = writeMoveDefinitionFile(templatesDefinition.moveDefs, MOVE_DEFINITION_FILE);
        const auto typeDefinitionFile = writeTypeDefinitionFile(templatesDefinition.typeDefs, TYPE_DEFINITION_FILE);
        const auto itemDefinitionFile = writeItemDefinitionFile(templatesDefinition.itemDefs, ITEM_DEFINITION_FILE);

        if (templatesDefinition.writeSchemas)
        {
            writeSchemas();
        }

        if (templatesDefinition.writeAllowedValues)
        {
            writeAllowedValueFile();
        }

        return ITemplatesDefinition
        {
            templatesDefinition.engine,
            templatesDefinition.outputDirectory,
            mechanicsDefinitionFile.data(),
            player1TeamDefinitionFile.data(),
            player2TeamDefinitionFile.data(),
            player1StrategyFile.data(),
            player2StrategyFile.data(),
            pkmnDefinitionFile.data(),
            moveDefinitionFile.data(),
            typeDefinitionFile.data(),
            itemDefinitionFile.data()
        };
    }
}
