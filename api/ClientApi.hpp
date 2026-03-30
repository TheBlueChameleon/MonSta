#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

extern "C" {
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    void engine_post_init();

    bool init(HostApi*);
    bool hasFeature(const char* const featureTag);
    bool hangUp();
    void terminateAbnormally();
}

// hack
static void force_link()
{
    volatile auto ptr0 = init;
    volatile auto ptr1 = hangUp;
    volatile auto ptr2 = terminateAbnormally;
    volatile auto ptr3 = hasFeature;
}

#endif // CLIENTAPI_HPP
