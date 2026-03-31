#include <cstring>

#include "memoryservice.hpp"

namespace MemoryService
{
    IMemoryService exportService()
    {
        return IMemoryService
        {
            allocate,
            createFromCstr,
            free
        };
    }

    IMemoryService::MemoryBlock allocate(const size_t size)
    {
        return IMemoryService::MemoryBlock(
                   new char[size],
                   size
               );
    }


    IMemoryService::MemoryBlock createFromView(const std::string_view view)
    {
        const auto size = view.size();
        IMemoryService::MemoryBlock result = allocate(size);
        std::strncpy(result.data, view.data(), size);

        return result;
    }

    IMemoryService::MemoryBlock createFromCstr(const char* const data)
    {
        const auto size = std::strlen(data);
        IMemoryService::MemoryBlock result = allocate(size);
        std::strncpy(result.data, data, size);

        return result;
    }

    void free(IMemoryService::MemoryBlock* stringData)
    {
        delete stringData->data;
        stringData->data = nullptr;
        stringData->size = 0;
    }

}
