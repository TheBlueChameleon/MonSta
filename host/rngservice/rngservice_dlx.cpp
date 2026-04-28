#include "rngservice.hpp"
#include "rngservice_dlx.hpp"

namespace RngService
{
    uint64_t HOST_API_CALL getEngineMin_dlx()
    {
        return getEngineMin();
    }

    uint64_t HOST_API_CALL getEngineMax_dlx()
    {
        return getEngineMax();
    }

    uint64_t HOST_API_CALL getRandomInt_dlx()
    {
        return getRandomInt();
    }

} // namespace RngService
