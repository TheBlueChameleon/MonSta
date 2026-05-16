#include <HostApi.hpp>

#include <services/IFileService.hpp>
#include <services/IJsonService.hpp>
#include <services/IVersionService.hpp>
#include <Version.hpp>

#include "constants.hpp"

#include "csvservice/csvservice.hpp"
#include "errorservice/errorservice.hpp"
#include "fileservice/fileservice.hpp"
#include "jsonservice/jsonservice.hpp"
#include "loggerservice/loggerservice.hpp"
#include "memoryservice/memoryservice.hpp"
#include "rngservice/rngservice.hpp"
#include "versionservice/versionservice.hpp"

#include "engine-base/base/globals.hpp"

#include "dlxinitialization.hpp"

const Version HOST_VERSION = Version(1,0,0,0);
const std::string APP_NAME = "TEST";
const std::string APP_VERSION = VersionService::to_string(HOST_VERSION);

HostApi getServices()
{
    return
    {
        HOST_VERSION,

        CsvService::exportService(),
        ErrorService::exportService(),
        FileService::exportService(),
        JsonService::exportService(),
        LoggerService::exportService(),
        MemoryService::exportService(),
        RngService::exportService(),
        VersionService::exportService()
    };
}

void initServices()
{
    static HostApi api = getServices();
    EngineBase::_hostApi = &api;
}
