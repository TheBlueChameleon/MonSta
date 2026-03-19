#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <IVersionService.hpp>
#include <Version.hpp>

#include "IJsonService.hpp"
#include "ILoggerService.hpp"

struct HostApi
{
    protected:
        HostApi(
            const Version         hostVersion,
            const ILoggerService  loggerService,
            const IVersionService versionService,
            const IJsonService    jsonService
        ) :
            hostVersion(hostVersion),
            loggerService(loggerService),
            versionService(versionService),
            jsonService(jsonService)
        {}

    public:
        const Version         hostVersion;
        const ILoggerService  loggerService;
        const IVersionService versionService;
        const IJsonService    jsonService;
};

#endif // HOSTAPI_HPP
