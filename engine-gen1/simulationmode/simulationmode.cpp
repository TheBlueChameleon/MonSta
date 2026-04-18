#include "services/loggerservice.hpp"
#include "services/jsonservice.hpp"

#include "base/enginebase.hpp"

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

#include "registry.hpp"
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
            LoggerService::info("### mechanics handling ###");
            LoggerService::info(mechanicsDefinitionFile.c_str());

            std::string mechanicsHandleName = Globals::jtag_base + mechanicsDefinitionFile.c_str();
            LoggerService::info("### tag gen'd ###");
            JHND_MECHANICSDEFINITION = JsonService::readValidatePatchAndAdd(
                                           IJsonServiceTypes::JsonTag(mechanicsHandleName.data()),
                                           mechanicsDefinitionFile,
                                           SchemaValidation::JTAG_MECHANICSDEFINITION
                                       );
        }
        catch (const EngineError& e)
        {
            LoggerService::info("### catch happened ###");
            LoggerService::info(e.what());
            eb.append(e);
            LoggerService::info("### append happened ###");
        }
    }

    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        ErrorBuffer eb;
        LoggerService::info("### enter setup ###");

        loadAndRegisterMechanicsDefinition(matchDefinition.mechanics, eb);

        auto child = JsonService::navigateTo(JHND_MECHANICSDEFINITION, SchemaValidation::JKEY_MECHANICS_GEN1MISS);

        LoggerService::infoF("### Gen1Miss active: {}",
                             (JsonService::getAsBool(child) ? "true" : "false")
                            );

        if (!eb.isClean())
        {
            LoggerService::info("### non clean state ###");
            LoggerService::info(eb.compileErrorMessage().data());
        }

        LoggerService::info("### exit ###");
    }
}
