#ifndef IMEMORYSERVICE_HPP
#define IMEMORYSERVICE_HPP

#include <cstddef>

#include <CallingConventions.hpp>

struct IMemoryService
{
    struct String
    {
        char*   data;
        size_t  size;
    };

    struct StringView
    {
        char*  data;
        size_t size;
    };

    struct StringArray
    {
        String* data;
        size_t  size;
    };

    struct StringViewArray
    {
        StringView* data;
        size_t      size;
    };

    IMemoryService::String(HOST_API_CALL* const allocateString_dlx)(const size_t size);
    IMemoryService::StringArray(HOST_API_CALL* const allocateStringArray_dlx)(const size_t size);
    IMemoryService::StringViewArray(HOST_API_CALL* const allocateStringViewArray_dlx)(const size_t size);

    IMemoryService::String(HOST_API_CALL* const copy_dlx)(const char* const string);
    IMemoryService::StringView(HOST_API_CALL* const wrap_dlx)(const char* const view);

    void (HOST_API_CALL* const freeString_dlx)(IMemoryService::String& data);
    void (HOST_API_CALL* const freeStringArray_dlx)(IMemoryService::StringArray& data);
    void (HOST_API_CALL* const freeStringViewArray_dlx)(IMemoryService::StringViewArray& data);

    // ====================================================================== //
    // legacy

    struct MemoryBlock
    {
        char*  data;
        size_t size;
    };

    MemoryBlock(HOST_API_CALL* const allocate)(const size_t size);
    MemoryBlock(HOST_API_CALL* const create)(const char* const data, size_t size);
    void (HOST_API_CALL* const free)(MemoryBlock* data);
};

#endif // IMEMORYSERVICE_HPP
