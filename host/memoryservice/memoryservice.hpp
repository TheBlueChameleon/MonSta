#ifndef MEMORYSERVICE_H
#define MEMORYSERVICE_H

#include <string_view>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService exportService();

    IMemoryService::MemoryBlock allocate(const size_t size);

    IMemoryService::MemoryBlock createFromView(const std::string_view view);

    IMemoryService::MemoryBlock createFromCstr(const char* const data);

    void free(IMemoryService::MemoryBlock* stringData);
}

#endif // MEMORYSERVICE_H
