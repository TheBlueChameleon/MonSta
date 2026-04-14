#ifndef ENTRYPOINT_SIMULATION_HPP
#define ENTRYPOINT_SIMULATION_HPP

#include <memory>

namespace OperationModes
{
    struct SimulationModeDefinition;
}

namespace SimulationMode
{
    void run(const OperationModes::SimulationModeDefinition& defs);
}

#endif // ENTRYPOINT_SIMULATION_HPP
