#include <functional>

#include <IFileService.hpp>
#include <IJsonService.hpp>
#include <IVersionService.hpp>
#include <Version.hpp>

#include "constants.hpp"

#include "fileservice/fileservice.hpp"
#include "jsonservice/jsonservice.hpp"
#include "loggerservice/loggerservice.hpp"
#include "versionservice/versionservice.hpp"

#include "hostapiwrapper.hpp"

HostApiWrapper HostApiWrapper::instance;

HostApiWrapper::HostApiWrapper() : HostApi(
        HOST_VERSION,

        FileService::exportService(),
        JsonService::exportService(),
        LoggerService::exportService(),
        MemoryService::exportService(),
        VersionService::exportService()
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
