#ifndef IMEMORYSERVICE_HPP
#define IMEMORYSERVICE_HPP

#include <cstddef>

#include <CallingConventions.hpp>

struct IMemoryService
{
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
