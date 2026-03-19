#include <functional>


#include "../json/jsonservice.hpp"

#include "../constants.hpp"

#include "hostapiwrapper.hpp"
#include "logger.hpp"
#include "versionservice.hpp"
#include "IJsonService.hpp"

HostApiWrapper HostApiWrapper::instance;

HostApiWrapper::HostApiWrapper() : HostApi(
        HOST_VERSION,
        new Logger(),
        IVersionService(
            &VersionService::equal,
            &VersionService::notEqual,
            &VersionService::lessThan,
            &VersionService::lessOrEqual,
            &VersionService::greaterThan,
            &VersionService::greaterOrEqual,
            &VersionService::streamInto,
            &VersionService::to_string
        ),
        IJsonService(
            &readJsonFile,
            &validateJsonAgainstJson
        )
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
