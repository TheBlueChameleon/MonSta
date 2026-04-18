#include "services/loggerservice.hpp"
#include "services/jsonservice.hpp"

#include "base/enginebase.hpp"

#include "simulationmode.hpp"

using namespace EngineBase;

namespace SimulationMode
{
    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        ErrorBuffer& eb
    )
    {
        try
        {
            //JsonService::readValidatePatchAndAdd()
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }

    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        ErrorBuffer eb;
        LoggerService::info("### enter setup ###");

        loadAndRegisterMechanicsDefinition(matchDefinition.mechanics, eb);

        LoggerService::info("### exit ###");
    }
}
