#ifndef MULTIHIT_HPP
#define MULTIHIT_HPP

#include <string_view>

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

            public:
                MultiHit();

                void execute(
                    SimulationMode::PokemonInstance& self,
                    SimulationMode::PokemonInstance& enemy,
                    SimulationMode::Scene& scene
                );
        };

    } // namespace Effects
} // namespace MetaDefinition

#endif // MULTIHIT_HPP
