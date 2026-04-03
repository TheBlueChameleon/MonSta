#ifndef HOSTAPI_HPP
#define HOSTAPI_HPP

#include "Version.hpp"

#include "IFileService.hpp"
#include "IJsonService.hpp"
#include "IMemoryService.hpp"
#include "ILoggerService.hpp"
#include "IVersionService.hpp"

struct HostApi
{
		const Version         hostVersion;

		const IFileService    fileService;
		const IJsonService    jsonService;
		const ILoggerService  loggerService;
		const IMemoryService  memoryService;
		const IVersionService versionService;
};

#endif // HOSTAPI_HPP
