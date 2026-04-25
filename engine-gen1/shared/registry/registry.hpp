#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <list>
#include <string>

#include <services/JsonService/IJsonService_Types.hpp>

#include "shared/defs/mechanicsdefinition.hpp"
#include "shared/defs/teamdefinition.hpp"

#include "pokemondatabase.hpp"
#include "typechart.hpp"

namespace Registry
{
    extern IJsonServiceTypes::JsonHandle JHND_MECHANICSDEFINITION;
    extern IJsonServiceTypes::JsonHandle JHND_PLAYER1_TEAMDEFINITION;
    extern IJsonServiceTypes::JsonHandle JHND_PLAYER2_TEAMDEFINITION;

    extern MetaDefinition::MechanicsDefinition mechanicsDefinition;
    extern MetaDefinition::TeamDefinition player1TeamDefinition;
    extern MetaDefinition::TeamDefinition player2TeamDefinition;

    extern TypeChart typeChart;
    extern PokemonDatabase pokemonDatabase;

    extern std::list<std::string> metaViolations;

} // namespace SimulationMode

#endif // REGISTRY_HPP
