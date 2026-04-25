#ifndef SIMULATIONMODE_HPP
#define SIMULATIONMODE_HPP

#include <runmodes/IMatchDefinition.hpp>

namespace SimulationMode
{
    void setupSimulationMode(const IMatchDefinition& matchDefinition);
    void registerEffects();
}

#endif // SIMULATIONMODE_HPP
