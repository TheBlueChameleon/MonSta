#ifndef MEMORYSERVICE_DLX_HPP
#define MEMORYSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/IMemoryService.hpp>

namespace MemoryService
{
    IMemoryService::String          HOST_API_CALL allocateString_dlx(const size_t size);
    IMemoryService::StringArray     HOST_API_CALL allocateStringArray_dlx(const size_t size);
    IMemoryService::StringViewArray HOST_API_CALL allocateStringViewArray_dlx(const size_t size);

    IMemoryService::String          HOST_API_CALL copy_dlx(const char* const string);
    IMemoryService::StringView      HOST_API_CALL wrap_dlx(const char* const view);

    void HOST_API_CALL freeString_dlx(IMemoryService::String& data);
    void HOST_API_CALL freeStringArray_dlx(IMemoryService::StringArray& data);
    void HOST_API_CALL freeStringViewArray_dlx(IMemoryService::StringViewArray& data);

    // ====================================================================== //
    // legacy

    IMemoryService::MemoryBlock HOST_API_CALL allocate_dlx(const size_t size);
    IMemoryService::MemoryBlock HOST_API_CALL create_dlx(const char* const data, const size_t size);
    void HOST_API_CALL freeString_dlx(IMemoryService::MemoryBlock* data);
}

#endif // MEMORYSERVICE_DLX_HPP
