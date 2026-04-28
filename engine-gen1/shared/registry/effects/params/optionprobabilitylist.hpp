#ifndef OPTIONPROBABILITYLIST_H
#define OPTIONPROBABILITYLIST_H

#include <map>

namespace MetaDefinition
{
    namespace EffectParams
    {
        class OptionProbabilityListBuilder;

        class OptionProbabilityList
        {
            private:
                std::map<int, double> intToProbabilitySums;

                OptionProbabilityList(std::map<int, double>& optionToProbabilitySums);

            public:
                int getRandomOption() const;

                friend class OptionProbabilityListBuilder;
        };

        class OptionProbabilityListBuilder
        {
            private:
                std::map<int, double> optionToProbability;

            public:
                OptionProbabilityListBuilder() = default;

                void addEntry(const std::pair<int, double> entry);
                void addEntry(const int i, const double probability);

                OptionProbabilityList build() const;
        };

    }   // namespace EffectParams
}       // namespace MetaDefinition

#endif // OPTIONPROBABILITYLIST_H
