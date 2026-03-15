#include "hostapiwrapper.hpp"
#include "logger.hpp"

HostApiWrapper HostApiWrapper::instance;


HostApiWrapper::HostApiWrapper() : HostApi(
        new Logger()
    )
{}

HostApiWrapper& HostApiWrapper::GetInstance()
{
    return instance;
}

HostApiWrapper* HostApiWrapper::GetInstancePtr()
{
    return &instance;
}

HostApiWrapper::~HostApiWrapper()
{
    delete logger;
}
