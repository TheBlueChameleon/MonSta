#ifndef HOSTAPIWRAPPER_HPP
#define HOSTAPIWRAPPER_HPP

#include <HostApi.hpp>

class HostApiWrapper : public HostApi
{
    private:
        HostApiWrapper();

        static HostApiWrapper instance;

    public:
        ~HostApiWrapper();

        HostApiWrapper(HostApiWrapper& other) = delete;
        void operator=(const HostApiWrapper&) = delete;

        static HostApiWrapper& GetInstance();
        static HostApiWrapper* GetInstancePtr();
};

#endif // HOSTAPIWRAPPER_HPP
