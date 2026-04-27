#include <ClientApi.hpp>
#include <FeatureTags.hpp>
#include <Version.hpp>

#include <base/errors.hpp>
#include <base/globals.hpp>

#include "shared/schemavalidationconstants.hpp"
#include "shared/registry/setup.hpp"

#include "simulationmode/simulationmode.hpp"

#include "templatesmode/templatesmode.hpp"

HOST_API_EXPORT
{
    const Version CLIENT_VERSION(0, 1, 0, 0);
    const Version MIN_HOST_VERSION(0, 1, 0, 0);

    void HOST_API_CALL hangUp()
    {}

    ITemplatesDefinition HOST_API_CALL startTemplatesMode(const ITemplatesDefinition templatesDefinition)
    {
        try
        {
            return TemplateMode::run(templatesDefinition);
        }
        catch (const EngineError& e)
        {
            EngineBase::passExceptionToHost(e);
        }

        return ITemplatesDefinition{};
    }

    void HOST_API_CALL setupSimulationMode(const IMatchDefinition matchDefinition)
    {
        try
        {
            return SimulationMode::setupSimulationMode(matchDefinition);
        }
        catch (const EngineError& e)
        {
            EngineBase::passExceptionToHost(e);
        }
    }
}

bool init_engine()
{
    LoggerService::debug("initializing engine data...");
    EngineBase::supportedFeatures =
    {
        FEATURE_SIMULATIONMODE_V1_0,
        FEATURE_TEMPLATEMODE_V1_0
    };

    try
    {
        SchemaValidation::registerMechanicsDefinition();
        SchemaValidation::registerSchemaTeamDefinition();

        Registry::registerEffects();

        LoggerService::debug("... done");
    }
    catch (const EngineError& e)
    {
        EngineBase::passExceptionToHost(e);
        return false;
    }

    return true;
}
