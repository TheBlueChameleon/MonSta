#include <random>
#include <thread>

#include <pcg_random.hpp>

#include "rngservice.hpp"
#include "rngservice_dlx.hpp"

namespace RngService
{
    // ====================================================================== //
    // static members

    static uint64_t getSeed64()
    {
        std::random_device rd;
        return (static_cast<uint64_t>(rd()) << 32) | rd();
    }

    static pcg32 makeRngThreadBased(const uint64_t seed)
    {
        const uint64_t tid_hash = std::hash<std::thread::id> {}(std::this_thread::get_id());
        const uint64_t stream = (tid_hash << 1u) | 1u;      // stream IDs must be odd

        return pcg32(seed, stream);
    }

    static const uint64_t seed = getSeed64();
    static thread_local pcg32 rng = makeRngThreadBased(seed);

    // ====================================================================== //
    // exported service

    IRngService exportService()
    {
        return IRngService
        {
            getEngineMin_dlx,
            getEngineMax_dlx,
            getRandomInt_dlx
        };
    }

    uint64_t getEngineMin()
    {
        return rng.min();
    }

    uint64_t getEngineMax()
    {
        return rng.max();
    }

    uint64_t getRandomInt()
    {
        return rng();
    }

} // namespace RngService
