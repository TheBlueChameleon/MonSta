#include <HostApi.hpp>

HostApi* hostapi;

extern "C" {
    void connectToHost(HostApi* api)
    {
        hostapi = api;
    }
}
