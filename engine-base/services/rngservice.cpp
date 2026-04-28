#include <limits>
#include <random>

#include "errorservice.hpp"
#include "services.hpp"
#include "rngservice.hpp"

using namespace Services;
using namespace ErrorService;

namespace RngService
{
    // ====================================================================== //
    // derived generator

    static Generator rngProxy;
    static std::uniform_real_distribution<double> distPercent(0,1);

    Generator::result_type Generator::operator()() const
    {
        return getRandomInt();
    }

    constexpr Generator::result_type Generator::min()
    {
        return std::numeric_limits<result_type>::min();
    }

    constexpr Generator::result_type Generator::max()
    {
        return std::numeric_limits<result_type>::max();
    }

    // ====================================================================== //
    // generator backed convenience

    double getRandomPercentage()
    {
        return distPercent(rngProxy);
    }

    bool getBiasedCoinFlip(const double pTrue)
    {
        return std::bernoulli_distribution(pTrue)(rngProxy);
    }

    int getIntBetween(const int lower, const int upper)
    {
        return std::uniform_int_distribution(lower, upper)(rngProxy);
    }

    double getRealBetween(const double lower, const double upper)
    {
        return std::uniform_real_distribution(lower, upper)(rngProxy);
    }

    // ====================================================================== //
    // direct exports

    uint64_t getEngineMin()
    {
        const auto result = rngService().getEngineMin();
        rethrowHostError();
        return result;
    }

    uint64_t getEngineMax()
    {
        const auto result = rngService().getEngineMax();
        rethrowHostError();
        return result;
    }

    uint64_t getRandomInt()
    {
        const auto result = rngService().getRandomInt();
        rethrowHostError();
        return result;
    }

}

