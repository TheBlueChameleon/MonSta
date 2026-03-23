#include <functional>

#include <IFileWriterService.hpp>
#include <IJsonService.hpp>
#include <IVersionService.hpp>
#include <Version.hpp>

#include "../filesystem/filewriterservice.hpp"

#include "../json/jsonservice.hpp"

#include "../logging/loggerservice.hpp"

#include "../constants.hpp"

#include "hostapiwrapper.hpp"
#include "versionservice.hpp"

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
        ),

        IFileWriterServie(
            &FileWriterService::getBase_cstr,
            &FileWriterService::setBase_cstr,
            &FileWriterService::write_cstr,
            &FileWriterService::writeBinary_cstr
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
