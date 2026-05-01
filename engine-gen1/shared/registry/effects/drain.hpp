#ifndef DRAIN_HPP
#define DRAIN_HPP

#include <string_view>

#include "shared/defs/hpamount.hpp"
#include "shared/defs/target.hpp"

#include "abstracteffecthandler.hpp"

namespace MetaDefinition
{
    namespace Effects
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

                void execute(SimulationMode::Scene& scene);
        };

    }   // namespace Effects
}       // namespace MetaDefinition

#endif // DRAIN_HPP
