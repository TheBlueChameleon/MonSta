#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include "ILogger.hpp"

struct HostApi
{
    protected:
        HostApi(ILogger* const logger) :
            logger(logger)
        {}

    public:
        ILogger* const logger;
};

#endif // HOSTAPI_HPP
