#include <cstring>

#include "memoryservice.hpp"
#include "memoryservice_dlx.hpp"

namespace MemoryService
{
    IMemoryService exportService()
    {
        return IMemoryService
        {
            allocate_dlx,
            create_dlx,
            free_dlx
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
        const auto size = view.size() + 1;
        IMemoryService::MemoryBlock result = allocate(size);
        std::strncpy(result.data, view.data(), size);

        return result;
    }

    IMemoryService::MemoryBlock createFromView(const std::span<std::byte> view)
    {
        const auto size = view.size();
        IMemoryService::MemoryBlock result = allocate(size);
        std::memcpy(result.data, view.data(), size);

        return result;
    }

    void free(IMemoryService::MemoryBlock* data)
    {
        delete data->data;
        data->data = nullptr;
        data->size = 0;
    }

}
