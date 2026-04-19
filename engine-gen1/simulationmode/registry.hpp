#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <services/JsonService/IJsonService_Types.hpp>

#include "mechanicsdefinition.hpp"
#include "teamdefinition.hpp"

namespace SimulationMode
{
    extern IJsonServiceTypes::JsonHandle JHND_MECHANICSDEFINITION;
    extern IJsonServiceTypes::JsonHandle JHND_PLAYER1_TEAMDEFINITION;
    extern IJsonServiceTypes::JsonHandle JHND_PLAYER2_TEAMDEFINITION;

    extern MechanicsDefinition mechanicsDefinition;
    extern TeamDefinition player1TeamDefinition;
    extern TeamDefinition player2TeamDefinition;

} // namespace SimulationMode

#endif // REGISTRY_HPP
