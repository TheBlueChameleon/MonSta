#include "intprobabilitylist.hpp"

namespace MetaDefinition
{
    namespace EffectParams
    {
        void IntProbabilityList::addEntry(const std::pair<int, double> entry)
        {
            addEntry(entry.first, entry.second);
        }

        void IntProbabilityList::addEntry(const int i, const double probability)
        {
            intToProbability.try_emplace(i, probability);
        }

        int IntProbabilityList::roll() const
        {

        }

    } // namespace EffectParams
} // namespace MetaDefinition
