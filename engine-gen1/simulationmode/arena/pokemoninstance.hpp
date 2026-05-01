#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include "shared/defs/stat.hpp"
#include "shared/defs/statstage.hpp"

#include "shared/registry/moves/move.hpp"

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

            int getSkipTurnCount() const;
            void reduceSkipTurnCount();
            void setSkipTurnCount(int amount);

            MetaDefinition::Move* getCurrentMove() const;
            void lockMoveNext(const MetaDefinition::Move* const move, const int turns);

    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
