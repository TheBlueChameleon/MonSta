#ifndef SERVICES_HPP
#define SERVICES_HPP

#include "errorservice.hpp"
#include "jsonservice.hpp"
#include "loggerservice.hpp"

const IErrorService   errorService();
const IJsonService&   jsonService();
const ILoggerService& loggerService();

#endif // SERVICES_HPP
