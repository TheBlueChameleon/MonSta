#include <ClientApi.hpp>
#include <FeatureTags.hpp>
#include <Version.hpp>

#include "globals.hpp"
#include "services.hpp"

extern "C" {
    const Version CLIENT_VERSION(0,1,0,0);
    const Version MIN_HOST_VERSION(0,1,0,0);
    const Version MAX_HOST_VERSION(2,0,0,0);

    ClientReturnCode hangUp()
    {
        return ClientReturnCode::SUCCESS;
    }
}

ClientReturnCode init_engine()
{
    Globals::supportedFeatures =
    {
        FEATURE_SIMULATIONMODE_V1_0,
        FEATURE_TEMPLATEMODE_V1_0
    };

    return ClientReturnCode::SUCCESS;
}
