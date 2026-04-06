#ifndef SERVICES_HPP
#define SERVICES_HPP

#include "errorservice.hpp"
#include "fileservice.hpp"
#include "jsonservice.hpp"
#include "loggerservice.hpp"

class HostApi;

class HostApiProxy
{
    private:
        HostApi* hostApi;

    public:
        HostApiProxy();
        ~HostApiProxy();

        HostApi& get();
        void rethrowHostError();
};

const IErrorService   errorService();
const IFileService    fileService();
const IJsonService&   jsonService();
const ILoggerService& loggerService();

#endif // SERVICES_HPP
