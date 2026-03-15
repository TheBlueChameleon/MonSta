#include <iostream>

#include <ClientApi.hpp>
#include <Version.hpp>

extern "C" {
    Version getClientVersion()
    {
        return Version(0,1,0,0);
    }
}

// this ensures "unused" functions from the static lib are still linked into the dyLib.
void dummyCalls()
{
    connectToHost(nullptr);
}
