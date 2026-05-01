#ifndef RNGSERVICE_HPP
#define RNGSERVICE_HPP

#include <cinttypes>

namespace RngService
{
    // TODO: get/set seed
    // TODO: channel from host defined thread number

    class Generator
    {
        public:
            using result_type = uint64_t;

            Generator() = default;

            result_type operator()() const;

            static constexpr result_type min();
            static constexpr result_type max();
    };

    double  getRandomPercentage();
    bool    getBiasedCoinFlip(const double pTrue = 0.5);
    int     getIntBetween(const int lower, const int upper);
    double  getRealBetween(const double lower, const double upper);

    uint64_t getEngineMin();
    uint64_t getEngineMax();

    uint64_t getRandomInt();
}

#endif // RNGSERVICE_HPP
