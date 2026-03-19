#include <iostream>
#include <string>

#include <HostApi.hpp>
#include <ClientApi.hpp>

HostApi* hostapi;

bool allVersionUtilsPresent(const IVersionService& vu)
{
    if (vu.equal == nullptr)
    {
        return false;
    }
    if (vu.notEqual == nullptr)
    {
        return false;
    }
    if (vu.lessThan == nullptr)
    {
        return false;
    }
    if (vu.lessOrEqual == nullptr)
    {
        return false;
    }
    if (vu.greaterThan == nullptr)
    {
        return false;
    }
    if (vu.greaterOrEqual == nullptr)
    {
        return false;
    }
    if (vu.streamInto == nullptr)
    {
        return false;
    }
    if (vu.to_string == nullptr)
    {
        return false;
    }

    return true;
}

bool hostVersionCompatible(const Version hostVersion, const IVersionService& vu)
{
    if (vu.lessThan(hostVersion, MINIMAL_HOST_VERSION))
    {
        return false;
    }
    return true;
}

extern "C" {
    bool connectToHost(HostApi* api)
    {
        if (api->logger == nullptr)
        {
            std::cerr << "Logger was not initialized!" << std::endl;
            return false;
        }

        ILogger& logger = *(api->logger);
        if (!allVersionUtilsPresent(api->versionService))
        {
            logger.critical("Not all VersionUtils have been initialized!");
            return false;
        }
        if (!hostVersionCompatible(api->hostVersion, api->versionService))
        {
            logger.critical("Host Version is {} but at least Version {} is required for this host.",
                            api->versionService.to_string(api->hostVersion),
                            api->versionService.to_string(MINIMAL_HOST_VERSION)
                           );
            return false;
        }

        hostapi = api;
        return true;
    }
}
