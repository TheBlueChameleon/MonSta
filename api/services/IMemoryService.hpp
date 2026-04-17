#ifndef IMEMORYSERVICE_H
#define IMEMORYSERVICE_H

#include <cstddef>

#include <CallingConventions.hpp>

struct IMemoryService
{
    struct MemoryBlock
    {
        char*  data;
        size_t size;
    };

    MemoryBlock(*const HOST_API_CALL allocate)(const size_t size);
    MemoryBlock(*const HOST_API_CALL create)(const char* const data, size_t size);
    void (*const HOST_API_CALL free)(MemoryBlock* data);
};

#endif // IMEMORYSERVICE_H
