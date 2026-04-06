#include "memoryservice.hpp"
#include "memoryservice_dlx.hpp"

namespace MemoryService
{
    IMemoryService::MemoryBlock HOST_API_CALL allocate_dlx(const size_t size)
    {
        return allocate(size);
    }

    IMemoryService::MemoryBlock HOST_API_CALL create_dlx(const char* const data, const size_t size)
    {
        return createFromView(std::span<std::byte>(
                                  reinterpret_cast<std::byte*>(const_cast<char*>(data)),
                                  size)
                             );
    }

    void HOST_API_CALL free_dlx(IMemoryService::MemoryBlock* data)
    {
        free(data);
    }
}
