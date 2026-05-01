#ifndef TRAP_HPP
#define TRAP_HPP

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
    {
        class Trap : public AbstractEffectHandler
        {
            public:
                static constexpr auto EFFECT_NAME = "Trap";

            private:
                const OptionProbabilityList hitCountProbabilities;

            public:
                Trap(const OptionProbabilityList& hitCountProbabilities);

                static Trap buildEffect(const std::string_view parameterDescriptor);

                void execute(SimulationMode::Scene& scene);
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // TRAP_HPP
