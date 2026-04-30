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

    IMemoryService::String(HOST_API_CALL* const allocateString)(const size_t size);
    IMemoryService::StringArray(HOST_API_CALL* const allocateStringArray)(const size_t size);
    IMemoryService::StringViewArray(HOST_API_CALL* const allocateStringViewArray)(const size_t size);

    IMemoryService::String(HOST_API_CALL* const copy)(const char* const string);
    IMemoryService::StringView(HOST_API_CALL* const wrap)(const char* const view);

    void (HOST_API_CALL* const freeString)(IMemoryService::String* const data);
    void (HOST_API_CALL* const freeStringArray)(IMemoryService::StringArray* const data);
    void (HOST_API_CALL* const freeStringViewArray)(IMemoryService::StringViewArray* const data);

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
