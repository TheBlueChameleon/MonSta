#include <iostream>

#include <HostApi.hpp>
#include <ClientApi.hpp>

HostApi* hostapi;

extern "C" {
    bool connectToHost(HostApi* api)
    {
        if (api->logger == nullptr)
        {
            std::cerr << "logger was not initialized!" << std::endl;
            return false;
        }

        // if (api->hostVersion < minimalHostVersion)
        // {
        //     api->logger->critical("foo");
        // }

        hostapi = api;
        return true;
    }
}
