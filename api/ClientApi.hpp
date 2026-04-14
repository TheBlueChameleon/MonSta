#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <ApiStatusCode.hpp>
#include <CallingConventions.hpp>
#include <HostApi.hpp>

#include <runmodes/TemplatesDefinition.hpp>

// ========================================================================== //
// exported to host

HOST_API_EXPORT
{
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    bool HOST_API_CALL init(HostApi* hostApi);
    void HOST_API_CALL hangUp();

    bool HOST_API_CALL hasFeature(const char* const featureTag);
    void HOST_API_CALL terminateAbnormally();

    void HOST_API_CALL setOverwrite(const bool overwrite);
    void HOST_API_CALL setCreateDirectories(const bool createDirectories);
    void HOST_API_CALL setDryMode(const bool dryMode);

    void HOST_API_CALL startTemplatesMode(const TemplatesDefinition* const templatesDefinition);
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
