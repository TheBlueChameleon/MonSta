#include <iostream>
#include <string>

#include <HostApi.hpp>
#include <ClientApi.hpp>

#include "services.hpp"

bool allLoggerServicesPresent(const ILoggerService& ls)
{
    return true;
}
bool allVersionServicesPresent(const IVersionService& vu)
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
    if (vu.to_string == nullptr)
    {
        return false;
    }

    return true;
}

void engine_post_init() {}

extern "C" {
    bool init(HostApi* api)
    {
        if (!allLoggerServicesPresent(api->loggerService))
        {
            std::cerr << "Logger was not initialized!" << std::endl;
            return false;
        }

        if (!allVersionServicesPresent(api->versionService))
        {
            api->loggerService.critical("Not all VersionUtils have been initialized!");
            return false;
        }

        hostApi = api;

        engine_post_init();
        return true;
    }

    void terminateAbnormally() {}
}
