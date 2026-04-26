#ifndef DRAIN_H
#define DRAIN_H

#include <string_view>

#include "params/numberinterpretation.hpp"
#include "params/target.hpp"

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    class Drain : public AbstractEffectHandler
    {
        private:
            const EffectParams::NumberInterpretation basis;
            const double value;
            const EffectParams::Target target;

        public:
            Drain(
                const EffectParams::NumberInterpretation basis,
                const double value,
                const EffectParams::Target target
            );
            static Drain buildEffect(const std::string_view parameterDescriptor);

            bool execute(
                SimulationMode::PokemonInstance& self,
                SimulationMode::PokemonInstance& enemy,
                SimulationMode::Scene& scene
            );
    };

} // namespace MetaDefinition

#endif // DRAIN_H
