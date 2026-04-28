#ifndef RNGSERVICE_DLX_HPP
#define RNGSERVICE_DLX_HPP

#include <cinttypes>

#include <CallingConventions.hpp>

namespace RngService
{
    uint64_t HOST_API_CALL getEngineMin_dlx();
    uint64_t HOST_API_CALL getEngineMax_dlx();

    uint64_t HOST_API_CALL getRandomInt_dlx();

} // namespace RngService

#endif // RNGSERVICE_DLX_HPP
