#include <base/errors.hpp>
#include <services/rngservice.hpp>

#include "optionprobabilitylist.hpp"

namespace MetaDefinition
{
    namespace EffectParams
    {
        // ================================================================== //
        // ProbabilityList

        OptionProbabilityList::OptionProbabilityList(std::map<int, double>& intToProbabilitySums):
            intToProbabilitySums(intToProbabilitySums)
        {
            double pSum = 0;
            for (const auto entry : intToProbabilitySums)
            {
                pSum += entry.second;
            }

            if (std::abs(1.0 - pSum) > (intToProbabilitySums.size() * 1E-10))
            {
                throw EngineError(
                    ApiStatusCode::ILLEGAL_CLIENT_STATE,
                    "Probabilities do not sum up to 100%"
                );
            }
        }

        int OptionProbabilityList::getRandomOption() const
        {
            double p = RngService::getRandomPercentage();
            for (const auto entry : intToProbabilitySums)
            {
                if (p < entry.second)
                {
                    return entry.first;
                }
            }

            throw EngineError(
                ApiStatusCode::ILLEGAL_CLIENT_STATE,
                "Rolled on non-normalized probability list"
            );
        }

        // ================================================================== //
        // Builder

        void OptionProbabilityListBuilder::addEntry(const std::pair<int, double> entry)
        {
            addEntry(entry.first, entry.second);
        }

        void OptionProbabilityListBuilder::addEntry(const int i, const double probability)
        {
            optionToProbability.try_emplace(i, probability);
        }

        OptionProbabilityList OptionProbabilityListBuilder::build() const
        {
            std::map<int, double> intToSums;
            double pSum = 0;
            for (const auto entry : optionToProbability)
            {
                pSum += entry.second;
                intToSums.try_emplace(entry.first, pSum);
            }

            if (std::abs(1.0 - pSum) > (optionToProbability.size() * 1E-10))
            {
                throw EngineError(
                    ApiStatusCode::INVALID_USER_INPUT,
                    "Probabilities do not sum up to 100%"
                );
            }

            return OptionProbabilityList(intToSums);
        }

    } // namespace EffectParams
} // namespace MetaDefinition
