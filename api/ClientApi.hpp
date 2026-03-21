#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

struct HostApi;

extern "C" {
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    void engine_post_init() __attribute__((weak));

    extern bool init(HostApi*);
    bool hangUp();
}

// hack
static void force_link()
{
    volatile auto ptr0 = &init;
    volatile auto ptr1 = &hangUp;
}

#endif // CLIENTAPI_HPP
