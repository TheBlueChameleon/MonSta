#ifndef HOSTAPIWRAPPER_HPP
#define HOSTAPIWRAPPER_HPP

#include <HostApi.hpp>

#include "logging/logger.hpp"

class HostApiWrapper : public HostApi
{
    private:
        static HostApiWrapper instance;

        HostApiWrapper();

    public:
        HostApiWrapper(HostApiWrapper& other) = delete;
        void operator=(const HostApiWrapper&) = delete;

        static HostApiWrapper& GetInstance();
        static HostApiWrapper* GetInstancePtr();
};

#endif // HOSTAPIWRAPPER_HPP
