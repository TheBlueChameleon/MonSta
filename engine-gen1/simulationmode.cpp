#include "services/loggerservice.hpp"

#include "simulationmode.hpp"

namespace SimulationMode
{
    void run(const IMatchDefinition& matchDefinition)
    {
        LoggerService::info("### hello ###");
    }
}
