#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <IVersionService.hpp>
#include <Version.hpp>

#include "IJsonService.hpp"
#include "ILogger.hpp"

struct HostApi
{
    protected:
        HostApi(
            ILogger* const logger,

            const Version hostVersion,
            const IVersionService versionService,
            const IJsonService    jsonService
        ) :
            hostVersion(hostVersion),
            logger(logger),
            versionService(versionService),
            jsonService(jsonService)
        {}

    public:
        ILogger* const logger;

        const Version         hostVersion;
        const IVersionService versionService;
        const IJsonService    jsonService;
};

#endif // HOSTAPI_HPP
