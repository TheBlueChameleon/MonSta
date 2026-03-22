#include "../../errors.hpp"

#include "../../api/clientwrapper.hpp"

#include "../../logging/loggerservice.hpp"

#include "../defs/safecast.hpp"

#include "entrypoint.hpp"

namespace SimulationMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs)
    {
        const SimulationModeDefinition& xDefs = RunDefinitionUtils::getAsSimulationModeDefinition(defs);
        LoggerService::setup(xDefs.logging);

        LoggerService::infoF("overwrite is {}", xDefs.overwrite);

        //ClientWrapper cw("./build-Desktop-Debug/libEngine-Gen1.so");
    }
}
