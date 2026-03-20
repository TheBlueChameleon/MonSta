#include <functional>

#include <IJsonService.hpp>

#include "../json/jsonservice.hpp"

#include "../constants.hpp"

#include "hostapiwrapper.hpp"
#include "versionservice.hpp"
#include "loggerservice.hpp"

HostApiWrapper HostApiWrapper::instance;

HostApiWrapper::HostApiWrapper() : HostApi(
        HOST_VERSION,
        ILoggerService(
            &LoggerService::trace,
            &LoggerService::debug,
            &LoggerService::info,
            &LoggerService::warn,
            &LoggerService::error,
            &LoggerService::critical
        ),
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
            &JsonService::readJsonFile,
            &JsonService::parseJson,
            &JsonService::validateJsonAgainstJson
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
