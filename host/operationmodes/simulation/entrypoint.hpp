#ifndef ENTRYPOINT_SIMULATION_HPP
#define ENTRYPOINT_SIMULATION_HPP

#include <memory>

struct BaseModeDefinition;

namespace SimulationMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_SIMULATION_HPP
