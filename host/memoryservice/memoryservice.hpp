#ifndef MEMORYSERVICE_HPP
#define MEMORYSERVICE_HPP

#include <span>
#include <string_view>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService exportService();

    IMemoryService::MemoryBlock allocate(const size_t size);

    IMemoryService::MemoryBlock createFromView(const std::string_view view);

    IMemoryService::MemoryBlock createFromView(const std::span<std::byte> view);

    void free(IMemoryService::MemoryBlock* data);
}

#endif // MEMORYSERVICE_HPP
