#include <runmodes/ITemplatesDefinition.hpp>

#include <services/loggerservice.hpp>

#include "shared/schemavalidationconstants.hpp"

#include "allowedvalueswriter.hpp"
#include "csvtemplateswriter.hpp"
#include "jsontemplateswriter.hpp"
#include "strategyfilewriter.hpp"
#include "templatesmode.hpp"

namespace TemplateMode
{
    const ITemplatesDefinition run(const ITemplatesDefinition& templatesDefinition)
    {
        if (templatesDefinition.writeSchemas)
        {
            writeSchemas();
        }

        if (templatesDefinition.writeAllowedValues)
        {
            writeAllowedValueFile(ALLOWED_VALUES_FILE);
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
            player1StrategyFile.data(),
            player2TeamDefinitionFile.data(),
            player2StrategyFile.data(),
            pkmnDefinitionFile.data(),
            moveDefinitionFile.data(),
            typeDefinitionFile.data(),
            itemDefinitionFile.data(),
            templatesDefinition.args
        };
    }
}
