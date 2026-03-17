#ifndef HOSTAPIWRAPPER_HPP
#define HOSTAPIWRAPPER_HPP

#include <HostApi.hpp>
#include "logger.hpp"

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

        static Logger& getLogger();
};

#endif // HOSTAPIWRAPPER_HPP
