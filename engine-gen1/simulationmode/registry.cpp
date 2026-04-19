#include "registry.hpp"

namespace SimulationMode
{
    IJsonServiceTypes::JsonHandle JHND_MECHANICSDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);
    IJsonServiceTypes::JsonHandle JHND_PLAYER1_TEAMDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);
    IJsonServiceTypes::JsonHandle JHND_PLAYER2_TEAMDEFINITION = IJsonServiceTypes::JsonHandle(nullptr);

    MechanicsDefinition mechanicsDefinition;
    TeamDefinition player1TeamDefinition;
    TeamDefinition player2TeamDefinition;

} // namespace SimulationMode
