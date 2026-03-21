#ifndef SERVICES_HPP
#define SERVICES_HPP

#include "loggerservice.hpp"

struct HostApi;

extern HostApi* hostApi;

const ILoggerService& loggerService();

#endif // SERVICES_HPP
