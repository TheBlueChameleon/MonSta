#include "api/clientwrapper.hpp"

#include "errorservice/errors.hpp"
#include "fileservice/fileservice.hpp"
#include "loggerservice/loggerservice.hpp"

#include "operationmodes/shared/utils.hpp"

#include "simulationmodeimplementation.hpp"
#include "simulationmodedefinition.hpp"

namespace OperationModes
{
    void runSimulationMode(const SimulationModeDefinition& defs)
    {
        setupLoggerService(defs.logging);
        setupFileService(defs);

        const auto enginePath = defs.paths.inputDirectory / defs.paths.engine;

        auto cw = ClientWrapper(enginePath);
        setupClientWriteOptions(cw, defs);

        cw.setupSimulationMode(
        {
            defs.match.mechanics.c_str(),
            defs.match.player1Team.c_str(),
            defs.match.player1Strategy.c_str(),
            defs.match.player2Team.c_str(),
            defs.match.player2Strategy.c_str(),
            defs.match.pkmnDefs.c_str(),
            defs.match.moveDefs.c_str(),
            defs.match.typeDefs.c_str(),
            defs.match.itemDefs.c_str(),
            defs.match.args.c_str()
        });
    }
}
