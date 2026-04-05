#ifndef IMEMORYSERVICE_H
#define IMEMORYSERVICE_H

#include <stddef.h>

struct IMemoryService
{
    struct MemoryBlock
    {
        char*  data;
        size_t size;
    };

    MemoryBlock(*const allocate)(const size_t size);
    MemoryBlock(*const create)(const char* const data);
    void (*const free)(MemoryBlock* stringData);
};

#endif // IMEMORYSERVICE_H
