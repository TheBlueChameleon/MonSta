#include <iostream>

#include <ClientApi.hpp>
#include <Version.hpp>

const Version CLIENT_VERSION(0,1,0,0);
const Version MIN_HOST_VERSION(0,1,0,0);
const Version MAX_HOST_VERSION(2,0,0,0);

extern "C" {
    Version getClientVersion()
    {
        return CLIENT_VERSION;
    }
}
