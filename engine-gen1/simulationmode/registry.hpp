#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <services/JsonService/IJsonService_Types.hpp>

#include "mechanicsdefinition.hpp"

namespace SimulationMode
{
    extern IJsonServiceTypes::JsonHandle JHND_MECHANICSDEFINITION;
    extern MechanicsDefinition mechanicsDefinition;

} // namespace SimulationMode

#endif // REGISTRY_HPP
