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

Logger& HostApiWrapper::getLogger()
{
    return *reinterpret_cast<Logger*>(HostApiWrapper::GetInstance().logger);
}

HostApiWrapper::~HostApiWrapper()
{
    delete logger;
}
