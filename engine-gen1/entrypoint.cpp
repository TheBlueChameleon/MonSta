#include <iostream>

#include <ClientApi.hpp>
#include <Version.hpp>

extern "C" {
    const Version CLIENT_VERSION(0,1,0,0);
    const Version MIN_HOST_VERSION(0,1,0,0);
    const Version MAX_HOST_VERSION(2,0,0,0);
}
