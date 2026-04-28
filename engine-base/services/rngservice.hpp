#ifndef RNGSERVICE_HPP
#define RNGSERVICE_HPP

#include <cinttypes>

namespace RngService
{
    class Generator
    {
        public:
            using result_type = uint64_t;
        private:
            const result_type _min;
            const result_type _max;

        public:
            Generator();
            const result_type min() const;
            const result_type max() const;
            result_type operator()() const;
    };

    Generator& getGeneratorInstance();

    double getRandomPercentage();
    bool   getBiasedCoinFlip(const double pTrue = 0.5);

    uint64_t getEngineMin();
    uint64_t getEngineMax();

    uint64_t getRandomInt();
}

#endif // RNGSERVICE_HPP
