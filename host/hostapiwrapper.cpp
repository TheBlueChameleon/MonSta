#include <functional>

#include "constants.hpp"
#include "hostapiwrapper.hpp"
#include "logger.hpp"
#include "versionutils.hpp"

HostApiWrapper HostApiWrapper::instance;

HostApiWrapper::HostApiWrapper() : HostApi(
        hostVersion,
        new Logger(),
        IVersionUtils(
            &VersionUtils::equal,
            &VersionUtils::notEqual,
            &VersionUtils::lessThan,
            &VersionUtils::lessOrEqual,
            &VersionUtils::greaterThan,
            &VersionUtils::greaterOrEqual,
            &VersionUtils::streamInto,
            &VersionUtils::to_string
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
