#include "memoryservice.hpp"
#include "memoryservice_dlx.hpp"

namespace MemoryService
{

    IMemoryService::String HOST_API_CALL allocateString_dlx(const size_t size)
    {
        return allocateString(size);
    }

    IMemoryService::StringArray HOST_API_CALL allocateStringArray_dlx(const size_t size)
    {
        return allocateStringArray(size);
    }

    IMemoryService::StringViewArray HOST_API_CALL allocateStringViewArray_dlx(const size_t size)
    {
        return allocateStringViewArray(size);
    }

    IMemoryService::String HOST_API_CALL copy_dlx(const char* const string)
    {
        return copy(std::string_view(string));
    }

    IMemoryService::StringView HOST_API_CALL wrap_dlx(const char* const view)
    {
        return wrap(std::string_view(view));
    }

    void HOST_API_CALL freeString_dlx(IMemoryService::String& data)
    {
        free(&data);
    }

    void HOST_API_CALL freeStringArray_dlx(IMemoryService::StringArray& data)
    {
        free(&data);
    }

    void HOST_API_CALL freeStringViewArray_dlx(IMemoryService::StringViewArray& data)
    {
        free(&data);
    }

    // ====================================================================== //
    // legacy

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

    void HOST_API_CALL freeString_dlx(IMemoryService::MemoryBlock* data)
    {
        free(data);
    }

}
