#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

extern const Version CLIENT_VERSION;
extern const Version MIN_HOST_VERSION;
extern const Version MAX_HOST_VERSION;

extern "C" {
    bool connectToHost(HostApi*);
}

// this ensures "unused" functions from the static lib are still linked into the dyLib.
static void dummyCalls()
{
    connectToHost(nullptr);
}

#endif // CLIENTAPI_HPP
