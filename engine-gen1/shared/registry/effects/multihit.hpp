#ifndef MULTIHIT_HPP
#define MULTIHIT_HPP

#include <string_view>

#include "shared/defs/optionprobabilitylist.hpp"

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class MultiHit : AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "MultiHit";

            private:
                OptionProbabilityList hitCountProbabilities;

            public:
                MultiHit(OptionProbabilityList probabilities);

                static MultiHit buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // MULTIHIT_HPP
