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
        OperationModes::setupLogger(defs.logging);

        LoggerService::infoF("overwrite is {}", defs.overwrite);

        ClientWrapper cw("./build-Desktop-Debug/libEngine-Gen1.so");
    }
}
