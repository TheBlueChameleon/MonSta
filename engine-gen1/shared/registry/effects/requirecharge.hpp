#ifndef REQUIRECHARGE_HPP
#define REQUIRECHARGE_HPP

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class RequireCharge : public AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "RequireCharge";

            private:
                OptionProbabilityList chargeTurnsProbabilities;

            public:
                RequireCharge(OptionProbabilityList chargeTurnsProbabilities);

                static RequireCharge buildEffect(const std::string_view parameterDescriptor);

                EffectEvaluationTime getEvaluationTime() override;

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // REQUIRECHARGE_HPP
