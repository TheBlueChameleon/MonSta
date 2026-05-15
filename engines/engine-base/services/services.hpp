#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <services/ICsvService.hpp>
#include <services/IErrorService.hpp>
#include <services/IFileService.hpp>
#include <services/IJsonService.hpp>
#include <services/ILoggerService.hpp>
#include <services/IMemoryService.hpp>
#include <services/IRngService.hpp>
#include <services/IVersionService.hpp>

namespace Services
{
    const ICsvService&      csvService();
    const IErrorService&    errorService();
    const IFileService&     fileService();
    const IJsonService&     jsonService();
    const ILoggerService&   loggerService();
    const IMemoryService&   memoryService();
    const IRngService&      rngService();
    const IVersionService&  versionService();
}

#endif // SERVICES_HPP
