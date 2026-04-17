#ifndef ICSVSERVICE_HPP
#define ICSVSERVICE_HPP

#include <cstddef>

struct ICsvService
{
    struct CsvOptions
    {
        char delimiter;
        char quoteChar;
    };

    struct CellData
    {
        char*  data;
        size_t size;
    };

    struct RowData
    {
        CellData* data;
        size_t    size;
    };
};

#endif // ICSVSERVICE_HPP
