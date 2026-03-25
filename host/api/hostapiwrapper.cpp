#include <functional>

#include <IFileService.hpp>
#include <IJsonService.hpp>
#include <IVersionService.hpp>
#include <Version.hpp>

#include "../fileservice/fileservice.hpp"

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

        IFileService(
            &FileService::getInputBasePath_cstr,
            &FileService::setInputBasePath_cstr,
            &FileService::getOutputBasePath_cstr,
            &FileService::setOutputBasePath_cstr,
            &FileService::read_cstr,
            &FileService::freeFileContents,
            &FileService::write_cstr,
            &FileService::writeBinary_cstr
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
