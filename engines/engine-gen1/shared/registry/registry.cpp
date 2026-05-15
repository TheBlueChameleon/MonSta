#include "registry.hpp"

using namespace MetaDefinition;

namespace Registry
{
    IJsonServiceTypes::JsonHandle JHND_MECHANICSDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);
    IJsonServiceTypes::JsonHandle JHND_PLAYER1_TEAMDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);
    IJsonServiceTypes::JsonHandle JHND_PLAYER2_TEAMDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);

    MechanicsDefinition mechanicsDefinition;
    TeamDefinition player1TeamDefinition;
    TeamDefinition player2TeamDefinition;

    TypeChart typeChart;
    PokemonDatabase pokemonDatabase;

    std::list<std::string> metaViolations;

} // namespace SimulationMode
