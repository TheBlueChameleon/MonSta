#ifndef IFILESERVICE_H
#define IFILESERVICE_H

#include <stddef.h>

#include <IMemoryService.hpp>

struct IFileService
{
    const char* const(*const getInputBase)();
    const char* const(*const getOutputBase)();

    IMemoryService::MemoryBlock(*const read)(const char* const filename);

    void (*const write)(const char* const filename, const char* const content);
    void (*const writeBinary)(const char* const filename, const void* const data, size_t length);
};

#endif // IFILESERVICE_H
