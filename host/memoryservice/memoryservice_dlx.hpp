#ifndef MEMORYSERVICE_DLX_HPP
#define MEMORYSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService::MemoryBlock HOST_API_CALL allocate_dlx(const size_t size);
    IMemoryService::MemoryBlock HOST_API_CALL create_dlx(const char* const data, const size_t size);
    void HOST_API_CALL free_dlx(IMemoryService::MemoryBlock* data);
}

#endif // MEMORYSERVICE_DLX_HPP
