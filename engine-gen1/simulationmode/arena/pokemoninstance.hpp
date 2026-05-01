#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include "shared/defs/stat.hpp"
#include "shared/defs/statstage.hpp"

#include "shared/registry/moves/move.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        public:
            static constexpr auto DELEGATE_BROKEN = -1;

        private:

        public:
            PokemonInstance();

            int takeDamage(const int amount);
            int recoverHealth(const int amount);

            int  getStat(const MetaDefinition::Stat stat) const;
            void setStat(const MetaDefinition::Stat stat, int value);

            int  getStatStage(const MetaDefinition::StatStage stat);
            void setStatStage(const MetaDefinition::StatStage stat, int value);
            void changeStatStage(const MetaDefinition::StatStage stat, int amount);

            int  getLastDamageReceived() const;
            void setLastDamageReceived(const int amount);

            int  getSkipTurnCount() const;
            void setSkipTurnCount(const int amount);
            void reduceSkipTurnCount();

            const MetaDefinition::Move* const getCurrentMove() const;
            void lockNextMove(const MetaDefinition::Move* const move, const int turns);
            void decreaseLockNextMoveCount();

            int  getAccumulatedDamage() const;
            void addToAccumulatedDamage(const int amount);
            void resetAccumulatedDamage();

            bool isTrapped() const;
            void setTrapped(bool value);

            void increaseRageCount();

            void decreaseTurnCounts();

    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
