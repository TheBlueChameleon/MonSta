#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <IVersionUtils.hpp>
#include <Version.hpp>

#include "ILogger.hpp"

struct HostApi
{
    protected:
        HostApi(
            const Version hostVersion,
            ILogger* const logger,
            const IVersionUtils versionUtils
        ) :
            hostVersion(hostVersion),
            logger(logger),
            versionUtils(versionUtils)
        {}

    public:
        const Version hostVersion;
        ILogger* const logger;
        const IVersionUtils versionUtils;
};

#endif // HOSTAPI_HPP
