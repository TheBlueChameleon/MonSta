#include "services/loggerservice.hpp"

#include "simulationmode.hpp"

namespace SimulationMode
{
    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        LoggerService::info("### hello ###");
    }
}
