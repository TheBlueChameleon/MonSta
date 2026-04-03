#ifndef SERVICES_HPP
#define SERVICES_HPP

#include "loggerservice.hpp"
#include "jsonservice.hpp"

const ILoggerService& loggerService();
const IJsonService&   jsonService();

#endif // SERVICES_HPP
