#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include <Version.hpp>

#include "ILogger.hpp"

struct HostApi
{
    protected:
        HostApi(
            Version hostVersion,
            ILogger* const logger
        ) :
            hostVersion(hostVersion),
            logger(logger)
        {}

    public:
        const Version hostVersion;
        ILogger* const logger;
};

#endif // HOSTAPI_HPP
