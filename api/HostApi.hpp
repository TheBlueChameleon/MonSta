#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <IVersionService.hpp>
#include <Version.hpp>

#include "IFileWriterService.hpp"
#include "IJsonService.hpp"
#include "ILoggerService.hpp"

struct HostApi
{
    protected:
        HostApi(
            const Version           hostVersion,
            const ILoggerService    loggerService,
            const IVersionService   versionService,
            const IJsonService      jsonService,
            const IFileWriterServie fileWriterService
        ) :
            hostVersion(hostVersion),
            loggerService(loggerService),
            versionService(versionService),
            jsonService(jsonService),
            fileWriterService(fileWriterService)
        {}

    public:
        const Version         hostVersion;
        const ILoggerService  loggerService;
        const IVersionService versionService;
        const IJsonService    jsonService;
        const IFileWriterServie fileWriterService;
};

#endif // HOSTAPI_HPP
