#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <ApiStatusCode.hpp>
#include <CallingConventions.hpp>
#include <Version.hpp>

#include <runmodes/IFileServiceDefinition.hpp>
#include <runmodes/IMatchDefinition.hpp>
#include <runmodes/ITemplatesDefinition.hpp>

// ========================================================================== //
// exported to host

struct HostApi;

HOST_API_EXPORT
{
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;

    bool HOST_API_CALL init(HostApi* hostApi);
    void HOST_API_CALL hangUp();

    bool HOST_API_CALL hasFeature(const char* const featureTag);
    void HOST_API_CALL terminateAbnormally();

    void HOST_API_CALL setFileServiceDefinition(const IFileServiceDefinition definition);

    ITemplatesDefinition HOST_API_CALL startTemplatesMode(const ITemplatesDefinition templatesDefinition);
    void HOST_API_CALL setupSimulationMode(const IMatchDefinition matchDefinition);
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

bool init_engine();

#endif // CLIENTAPI_HPP
