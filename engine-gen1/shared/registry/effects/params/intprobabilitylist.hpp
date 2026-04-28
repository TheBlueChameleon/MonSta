#ifndef INTPROBABILITYLIST_HPP
#define INTPROBABILITYLIST_HPP

#include <map>

namespace MetaDefinition
{
    namespace EffectParams
    {
        class IntProbabilityList
        {
            private:
                std::map<int, double> intToProbability;

            public:
                IntProbabilityList() = default;

                void addEntry(const std::pair<int, double> entry);
                void addEntry(const int i, const double probability);

                int roll() const;
        };

    } // namespace EffectParams
} // namespace MetaDefinition

#endif // INTPROBABILITYLIST_HPP
