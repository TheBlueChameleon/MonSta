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
                const double paybackMultiplyer;

            public:
                AccumulateAndPayBack(const double paybackMultiplyer);

                static AccumulateAndPayBack buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // ACCUMULATEANDPAYBACK_HPP
