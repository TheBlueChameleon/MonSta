#include <ClientApi.hpp>
#include <FeatureTags.hpp>
#include <Version.hpp>

#include "services/services.hpp"

#include "enginebase.hpp"
#include "errors.hpp"
#include "globals.hpp"

HOST_API_EXPORT
{
    const Version CLIENT_VERSION(0, 1, 0, 0);
    const Version MIN_HOST_VERSION(0, 1, 0, 0);
    const Version MAX_HOST_VERSION(2, 0, 0, 0);

    void HOST_API_CALL hangUp()
    {}

    void HOST_API_CALL startTemplatesMode()
    {
        try
        {
            LoggerService::info("entry into dylib");

            LoggerService::info("requesting by tag");
            auto handle = JsonService::get(":storage:/host/:validation:/templates.json");
            LoggerService::infoF("get returned {}", handle.data);

            LoggerService::infoF("contains 'properties' {}", JsonService::contains(handle, "properties"));
            LoggerService::infoF("contains 'foo'        {}", JsonService::contains(handle, "foo"));

            auto subHandle = JsonService::navigateTo(handle, "/properties/logging");
            LoggerService::infoF("navigateTo returned {}", subHandle.data);
            LoggerService::infoF("contains '$ref'     {}", JsonService::contains(subHandle, "$ref"));
            LoggerService::infoF("contains '$foo'     {}", JsonService::contains(subHandle, "$foo"));

            auto textHandle = JsonService::navigateTo(subHandle, "/$ref");
            LoggerService::infoF("navigateTo returned    {}", textHandle.data);
            LoggerService::infoF("text handle is string: {}", JsonService::isString(textHandle));
            LoggerService::infoF("text handle content:   {}", JsonService::getAsString(textHandle));
        }
        catch (const EngineError& e)
        {
            EngineBase::handleException(e);
        }
    }
}

bool init_engine()
{
    Globals::supportedFeatures =
    {
        FEATURE_SIMULATIONMODE_V1_0,
        FEATURE_TEMPLATEMODE_V1_0
    };

    return true;
}
