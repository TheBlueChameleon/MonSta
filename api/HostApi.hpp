#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <IVersionService.hpp>
#include <Version.hpp>

#include "IFileService.hpp"
#include "IJsonService.hpp"
#include "ILoggerService.hpp"

struct HostApi
{
    protected:
        HostApi(
            const Version           hostVersion,

            const IFileService      fileService,
            const IJsonService      jsonService,
            const ILoggerService    loggerService,
            const IVersionService   versionService
        ) :
            hostVersion(hostVersion),

            fileService(fileService),
            jsonService(jsonService),
            loggerService(loggerService),
            versionService(versionService)
        {}

    public:
        const Version         hostVersion;

        const IFileService    fileService;
        const IJsonService    jsonService;
        const ILoggerService  loggerService;
        const IVersionService versionService;
};

#endif // HOSTAPI_HPP
