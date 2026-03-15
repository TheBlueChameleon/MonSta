#ifndef CLIENTAPI_HPP
#define CLIENTAPI_HPP

#include <HostApi.hpp>

extern Version clientVersion;
extern Version minimalHostVersion;

extern "C" {
    bool connectToHost(HostApi*);
}

#endif // CLIENTAPI_HPP
