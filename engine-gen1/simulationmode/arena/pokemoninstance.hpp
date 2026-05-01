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
            static constexpr auto KNOCKOUT = -1;

        private:

        public:
            PokemonInstance();

            int takeDamage(const int amount);
            int recoverHealth(const int amount);

            int  getLastDamageReceived() const;
            void setLastDamageReceived(const int amount);

            int  getStat(const MetaDefinition::Stat stat) const;
            void setStat(const MetaDefinition::Stat stat, int value);

            int  getStatStage(const MetaDefinition::StatStage stat);
            void setStatStage(const MetaDefinition::StatStage stat, int value);
            void changeStatStage(const MetaDefinition::StatStage stat, int amount);

            double getHitChance();
            double getStrikeChance();

            bool isEscapePrevented() const;
            void setEscapePrevented(const bool value);

            bool isSemiInvulnerable() const;
            void setSemiInvulnerable(const bool value);

            int  getSkipTurnCount() const;
            void setSkipTurnCount(const int amount);
            void decreaseSkipTurnCount();

            int  getSleepCount() const;
            void setSleepCount(const int value);
            void decreaseSleepCount();

            int  getBoundCount() const;
            void setBoundCount(const int value);
            void decreaseBoundCount();

            const MetaDefinition::Move* const getCurrentMove() const;
            const MetaDefinition::Move* const getLockedInMove() const;
            int  getLockInCount() const;
            void lockNextMove(const MetaDefinition::Move* const move, const int turns);
            void decreaseLockNextMoveCount();

            int  getAccumulatedDamage() const;
            void addToAccumulatedDamage(const int amount);
            void resetAccumulatedDamage();

            void increaseRageCount();

            void decreaseTurnCounts();

    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
