#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <ClientReturnCodes.hpp>
#include <HostApi.hpp>

// ========================================================================== //
// exported to host

extern "C" {
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    ClientReturnCode init(HostApi* hostApi);
    ClientReturnCode hangUp();

    bool hasFeature(const char* const featureTag);
    void terminateAbnormally();

    ClientReturnCode startTemplatesMode();
}

// -------------------------------------------------------------------------- //
// ensure availability of exported functions in resulting SO/DLL

static void force_link()
{
    volatile auto ptr0 = init;
    volatile auto ptr1 = hangUp;
    volatile auto ptr2 = terminateAbnormally;
    volatile auto ptr3 = hasFeature;
}

// ========================================================================== //
// called internally

ClientReturnCode init_engine();


#endif // CLIENTAPI_HPP
