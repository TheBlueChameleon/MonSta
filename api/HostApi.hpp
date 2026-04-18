#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include "Version.hpp"

#include "services/ICsvService.hpp"
#include "services/IErrorService.hpp"
#include "services/IFileService.hpp"
#include "services/IJsonService.hpp"
#include "services/IMemoryService.hpp"
#include "services/ILoggerService.hpp"
#include "services/IVersionService.hpp"

struct HostApi
{
    const Version           hostVersion;

    const ICsvService       csvService;
    const IErrorService     errorService;
    const IFileService      fileService;
    const IJsonService      jsonService;
    const ILoggerService    loggerService;
    const IMemoryService    memoryService;
    const IVersionService   versionService;
};

#endif // HOSTAPI_HPP
