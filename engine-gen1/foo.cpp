#include <iostream>

#include <ClientApi.hpp>
#include <Version.hpp>

Version clientVersion(0,1,0,0);
Version minimalHostVersion(0,1,0,0);

extern "C" {
    Version getClientVersion()
    {
        return clientVersion;
    }
}

// this ensures "unused" functions from the static lib are still linked into the dyLib.
void dummyCalls()
{
    connectToHost(nullptr);
}
