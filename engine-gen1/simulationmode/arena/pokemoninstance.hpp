#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include "shared/defs/stat.hpp"
#include "shared/defs/statstage.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        private:

        public:
            PokemonInstance();

            int takeDamage(const int amount);
            int recoverHealth(const int amount);

            int getStat(const  MetaDefinition::Stat stat) const;
            void setStat(const MetaDefinition::Stat stat, int value);

            int getStatStage(const     MetaDefinition::StatStage stat);
            void setStatStage(const    MetaDefinition::StatStage stat, int value);
            void changeStatStage(const MetaDefinition::StatStage stat, int amount);
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
