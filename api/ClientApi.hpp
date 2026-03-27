#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

extern "C" {
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    void engine_post_init() __attribute__((weak));

    bool init(HostApi*);
    bool hangUp();
    void terminateAbnormally();
}

// hack
static void force_link()
{
    volatile auto ptr0 = init;
    volatile auto ptr1 = hangUp;
    volatile auto ptr2 = terminateAbnormally;
}

#endif // CLIENTAPI_HPP
