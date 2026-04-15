#include "api/clientwrapper.hpp"

#include "errorservice/errors.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "simulationmodeimplementation.hpp"
#include "simulationmodedefinition.hpp"

namespace OperationModes
{
    void runSimulationMode(const SimulationModeDefinition& defs)
    {
        setupLoggerService(defs.logging);
        setupFileService(defs, defs.simulator.outputDir);

        auto cw = ClientWrapper(defs.simulator.engine);
        setupClientWriteOptions(cw, defs);
    }
}
