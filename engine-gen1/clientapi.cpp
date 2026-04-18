#include <ClientApi.hpp>
#include <FeatureTags.hpp>
#include <Version.hpp>

#include "enginebase.hpp"
#include "errors.hpp"
#include "globals.hpp"

#include "schemavalidationconstants.hpp"
#include "templatesmode.hpp"
#include "simulationmode.hpp"

HOST_API_EXPORT
{
    const Version CLIENT_VERSION(0, 1, 0, 0);
    const Version MIN_HOST_VERSION(0, 1, 0, 0);
    const Version MAX_HOST_VERSION(2, 0, 0, 0);

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
    Globals::supportedFeatures =
    {
        FEATURE_SIMULATIONMODE_V1_0,
        FEATURE_TEMPLATEMODE_V1_0
    };

    SchemaValidation::registerMechanicsDefinition();
    SchemaValidation::registerSchemaTeamDefinition();

    LoggerService::debug("... done");
    return true;
}
