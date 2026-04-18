#ifndef TEMPLATESMODE_HPP
#define TEMPLATESMODE_HPP

struct ITemplatesDefinition;

namespace TemplateMode
{
    const auto MECHANICS_DEFINITION_FILE   = "mechanics.json";
    const auto PLAYER1_TEAMDEFINITION_FILE = "player1Team.json";
    const auto PLAYER2_TEAMDEFINITION_FILE = "player2Team.json";
    const auto PLAYER1_STRATEGY_FILE       = "player1Strategy.lua";
    const auto PLAYER2_STRATEGY_FILE       = "player2Strategy.lua";
    const auto PKMN_DEFINITION_FILE        = "pokemonDefinitions.csv";
    const auto MOVE_DEFINITION_FILE        = "moveDefinitions.csv";
    const auto TYPE_DEFINITION_FILE        = "typeDefinitions.csv";
    const auto ITEM_DEFINITION_FILE        = "itemDefinitions.csv";
    const auto ALLOWED_VALUES_FILE         = "allowedValues.txt";

    const ITemplatesDefinition run(const ITemplatesDefinition& templatesDefinition);
}

#endif // TEMPLATESMODE_HPP
