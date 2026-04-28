#ifndef IRNGSERVICE_HPP
#define IRNGSERVICE_HPP

#include <stdint.h>

#include <CallingConventions.hpp>

struct IRngService
{
    uint64_t (HOST_API_CALL* const getEngineMin)();
    uint64_t (HOST_API_CALL* const getEngineMax)();
    uint64_t (HOST_API_CALL* const getRandomInt)();
};

#endif // IRNGSERVICE_HPP
