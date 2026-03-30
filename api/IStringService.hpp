#ifndef ISTRINGSERVICE_HPP
#define ISTRINGSERVICE_HPP

#include <stddef.h>

struct IStringService
{
    struct StringData
    {
        char*  data;
        size_t size;
    };

    StringData(*const allocate)(const size_t size);
    StringData(*const create)(const char* const data);
    void (*const free)(StringData* stringData);
};

#endif // ISTRINGSERVICE_HPP
