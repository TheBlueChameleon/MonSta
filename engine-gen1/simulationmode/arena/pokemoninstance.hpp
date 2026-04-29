#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include "stat.hpp"
#include "statstage.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        private:

        public:
            PokemonInstance();

            int takeDamage(const int amount);
            int recoverHealth(const int amount);

            int getStat(const Stat stat) const;
            void setStat(const Stat stat, int value);

            int getStatStage(const StatStage);
            void setStatStage(const StatStage stat, int value);
            void changeStatStage(const StatStage stat, int amount);
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
