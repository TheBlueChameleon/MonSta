#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

extern "C" {
    extern const Version CLIENT_VERSION;
    extern const Version MIN_HOST_VERSION;
    extern const Version MAX_HOST_VERSION;

    bool init(HostApi*);
    bool hangUp();
}

#endif // CLIENTAPI_HPP
