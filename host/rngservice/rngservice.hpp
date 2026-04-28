#ifndef RNGSERVICE_HPP
#define RNGSERVICE_HPP

#include <stdint.h>

#include <services/IRngService.hpp>

namespace RngService
{
    IRngService exportService();

    uint64_t getEngineMin();
    uint64_t getEngineMax();

    uint64_t getRandomInt();

} // namespace RngService

#endif // RNGSERVICE_HPP
