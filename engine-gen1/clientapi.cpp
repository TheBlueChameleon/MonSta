#include <ClientApi.hpp>
#include <FeatureTags.hpp>
#include <Version.hpp>

#include "services/fileservice.hpp"
#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

#include "enginebase.hpp"
#include "errors.hpp"
#include "globals.hpp"

#include "schemavalidationconstants.hpp"

HOST_API_EXPORT
{
    const Version CLIENT_VERSION(0, 1, 0, 0);
    const Version MIN_HOST_VERSION(0, 1, 0, 0);
    const Version MAX_HOST_VERSION(2, 0, 0, 0);

    void HOST_API_CALL hangUp()
    {}

    void HOST_API_CALL startTemplatesMode(const TemplatesDefinition* const templatesDefinition)
    {
        try
        {
            auto handleTeamDef = JsonService::get(SchemaValidation::JTAG_TEAMDEFINITION);
            auto content = JsonService::dump(handleTeamDef);
            FileService::write("foo.json", content.getAsStringView());

            auto handleXDef = JsonService::get(SchemaValidation::JTAG_MECHANICSDEFINITION);
            auto contentX = JsonService::dump(handleXDef);
            FileService::write("bar.json", contentX.getAsStringView());
        }
        catch (const EngineError& e)
        {
            EngineBase::handleException(e);
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
