#ifndef CSVSERVICE_DLX_HPP
#define CSVSERVICE_DLX_HPP

#include <CallingConventions.hpp>

#include <services/ICsvService.hpp>

namespace CsvService
{
    struct CsvHandle
    {
        void* data;
    };
}

#endif // CSVSERVICE_DLX_HPP
