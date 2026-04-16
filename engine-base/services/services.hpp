#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <services/IErrorService.hpp>
#include <services/IFileService.hpp>
#include <services/IJsonService.hpp>
#include <services/ILoggerService.hpp>
#include <services/IMemoryService.hpp>

class HostApi;

void rethrowHostError();

const IErrorService&  errorService();
const IFileService&   fileService();
const IJsonService&   jsonService();
const ILoggerService& loggerService();
const IMemoryService& memoryService();

#endif // SERVICES_HPP
