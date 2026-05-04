#ifndef ACCUMULATEANDPAYBACK_HPP
#define ACCUMULATEANDPAYBACK_HPP

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class AccumulateAndPayBack : public AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "AccumulateAndPayBack";

            private:
                static constexpr double paybackMultiplyer = 2.0;
                const OptionProbabilityList chargeTurnsProbabilities;

            private:
                void dealDamage(SimulationMode::PokemonInstance& self, SimulationMode::PokemonInstance& enemy);

            public:
                AccumulateAndPayBack(const OptionProbabilityList& chargeTurnsProbabilities);

                static AccumulateAndPayBack buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // ACCUMULATEANDPAYBACK_HPP
