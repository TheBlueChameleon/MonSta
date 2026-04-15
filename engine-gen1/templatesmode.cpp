#include <runmodes/ITemplatesDefinition.hpp>

#include "services/fileservice.hpp"
#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

#include "schemavalidationconstants.hpp"
#include "templatesmode.hpp"

namespace TemplateMode
{
    static std::string writeMechanicsDefinitionFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writeTeamDefinitionFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writeStrategyFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writePkmnDefinitionFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writeMoveDefinitionFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writeTypeDefinitionFile(
        const std::string inputName,
        const std::string defaultName
    )
    {
        if (!inputName.empty())
        {
            return inputName;
        }


        return defaultName;
    }

    static std::string writeItemDefinitionFile(
        const std::string inputName,
        const std::string defaultName
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

    void run(const ITemplatesDefinition& templatesDefinition)
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
    }
}
