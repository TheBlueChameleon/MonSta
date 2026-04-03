#include "errors.hpp"

#include "api/clientwrapper.hpp"

#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "entrypoint.hpp"
#include "simulationmodedefinition.hpp"

namespace SimulationMode
{
    void run(const SimulationModeDefinition& defs)
    {
        OperationModes::setupLoggerService(defs.logging);
        OperationModes::setupFileService(defs, defs.simulator.outputDir);

        LoggerService::infoF("overwrite is {}", defs.overwrite);

        auto cw = ClientWrapper(defs.simulator.engine);
    }
}
