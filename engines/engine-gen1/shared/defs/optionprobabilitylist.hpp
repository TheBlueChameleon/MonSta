#ifndef OPTIONPROBABILITYLIST_HPP
#define OPTIONPROBABILITYLIST_HPP

#include <map>

namespace MetaDefinition
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

}       // namespace MetaDefinition

#endif // OPTIONPROBABILITYLIST_HPP
