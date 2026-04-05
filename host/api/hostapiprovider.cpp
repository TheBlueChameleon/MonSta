#include <HostApi.hpp>

#include <services/IFileService.hpp>
#include <services/IJsonService.hpp>
#include <services/IVersionService.hpp>
#include <Version.hpp>

#include "constants.hpp"

#include "errorservice/errorservice.hpp"
#include "fileservice/fileservice.hpp"
#include "jsonservice/jsonservice.hpp"
#include "loggerservice/loggerservice.hpp"
#include "versionservice/versionservice.hpp"

#include "hostapiprovider.hpp"

namespace HostApiProvider
{
    HostApi createHostApi()
    {
        return HostApi
        {
            HOST_VERSION,

            ErrorService::exportService(),
            FileService::exportService(),
            JsonService::exportService(),
            LoggerService::exportService(),
            MemoryService::exportService(),
            VersionService::exportService()
        };
    }
}
