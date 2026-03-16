#include <iostream>

#include <ClientApi.hpp>
#include <Version.hpp>

Version CLIENT_VERSION(0,1,0,0);
Version MINIMAL_HOST_VERSION(0,1,0,0);

extern "C" {
    Version getClientVersion()
    {
        return CLIENT_VERSION;
    }
}
