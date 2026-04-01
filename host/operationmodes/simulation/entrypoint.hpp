#ifndef ENTRYPOINT_SIMULATION_HPP
#define ENTRYPOINT_SIMULATION_HPP

#include <memory>

struct SimulationModeDefinition;

namespace SimulationMode
{
    void run(const SimulationModeDefinition& defs);
}

#endif // ENTRYPOINT_SIMULATION_HPP
