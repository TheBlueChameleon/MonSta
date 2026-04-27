#ifndef DRAIN_H
#define DRAIN_H

#include <string_view>

#include "params/hpamount.hpp"
#include "params/target.hpp"

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    class Drain : public AbstractEffectHandler
    {
        public:
            static constexpr auto EFFECT_NAME = "Drain";

        private:
            const EffectParams::HPAmount amount;
            const EffectParams::Target   target;

        public:
            Drain(
                const EffectParams::HPAmount amount,
                const EffectParams::Target   target
            );
            static Drain buildEffect(const std::string_view parameterDescriptor);

            void execute(
                SimulationMode::PokemonInstance& self,
                SimulationMode::PokemonInstance& enemy,
                SimulationMode::Scene& scene
            );
    };

} // namespace MetaDefinition

#endif // DRAIN_H
