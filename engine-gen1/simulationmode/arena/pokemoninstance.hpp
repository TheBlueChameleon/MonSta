#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include "shared/registry/effects/params/statstage.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        public:
            PokemonInstance();

            void takeDamage(const int amount);
            void recoverHealth(const int amount);
            void changeStatStage(const MetaDefinition::EffectParams::StatStage stat, int amount);
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
