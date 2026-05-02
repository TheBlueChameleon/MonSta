#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include <set>

#include "shared/defs/stat.hpp"
#include "shared/defs/statstage.hpp"
#include "shared/defs/statuscondition.hpp"

#include "shared/registry/moves/move.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        public:
            static constexpr auto USE_DEFAULT = -1;
            // static constexpr auto FOREVER = -2? int_max?

        private:
            int hp;
            int hpMax;
            int  substituteHP;
            bool knockedOutSubstitute;
            int  lastDamageReceived;
            int  accumulatedDamage;

            int atk;
            int def;
            int spc;
            int spd;

            int stageAtk;
            int stageDef;
            int stageSpc;
            int stageSpd;
            int stageAccuracy;
            int stageEvasion;
            int stageCritRate;

            MetaDefinition::NonVolatileStatusCondition nvStatus;
            std::set<MetaDefinition::VolatileStatusCondition> volatileStatus;

            int  skipTurnCounter;
            int  sleepCounter;
            int  confusionCounter;
            int  boundCounter;
            int  toxicCounter;
            int  rageCounter;
            bool useRageCounter;

            bool protectCancelLockedMove;
            bool lockedMoveReleaseTurn;
            int  lockedMoveCounter;
            const MetaDefinition::Move* lockedMove;
            const MetaDefinition::Move* selectedMove;

            bool preventEscape;
            bool semiInvulnerable;

        private:
            int  takeDirectDamage(const int amount);
            int  takeSubstituteDamage(const int amount);
            void setLastDamageReceived(const int amount);

            void   recalculateStats();
            double getStageMultiplier(const int stage, const std::string_view stageName) const;

            void setSubstituteHP(const int value);
            void setKnockedOutSubstitute(bool value);

            void setSleepCounter(int value);
            void decreaseSleepCounter();
            void setConfusionCounter(const int turns);
            void decreseConfusionCounter();
            void setBoundCounter(const int turns);
            void decreaseBoundCounter();
            void decreaseSkipTurnCounter();
            void decreaseLockedMoveCounter();

            void clearPersistentFlags();
            void clearTemporaryFlags();

        public:
            PokemonInstance() = default;

            int takeDamage(const int amount);
            int recoverHealth(const int amount);
            int getLastDamageReceived() const;

            int  getStat(const MetaDefinition::Stat stat) const;
            void setStat(const MetaDefinition::Stat stat, int value);

            int  getStatStage(const MetaDefinition::StatStage stat);
            void setStatStage(const MetaDefinition::StatStage stat, int value);
            void changeStatStage(const MetaDefinition::StatStage stat, int amount);

            double getStageMultiplier(const MetaDefinition::StatStage stat) const;

            bool isEscapePrevented() const;
            void setEscapePrevented(const bool value);

            bool isSemiInvulnerable() const;
            void setSemiInvulnerable(const bool value);

            int  getSubstituteHP() const;
            bool getKnockedOutSubstitute() const;
            void installSubstitute(const int substituteHp);

            int  getSkipTurnCounter() const;
            void setSkipTurnCounter(const int turns);

            int getSleepCounter() const;
            int getBoundCounter() const;
            int getConfusionCounter() const;

            const MetaDefinition::Move* const getSelectedMove() const;
            const MetaDefinition::Move* const getLockedMove() const;
            bool getProtectCancelLockedMove() const;
            int  getLockedMoveCounter() const;
            bool isLockedMoveReleaseTurn() const;
            void lockMove(const MetaDefinition::Move* const move, const int turns, const bool protectCancel = false);
            void cancelLockedMove();
            bool canChooseMove() const;

            int  getAccumulatedDamage() const;
            void addToAccumulatedDamage(const int amount);
            void resetAccumulatedDamage();

            void decreaseTurnCounts();

            MetaDefinition::NonVolatileStatusCondition getNvStatus() const;
            MetaDefinition::NonVolatileStatusCondition setNvStatus(
                MetaDefinition::NonVolatileStatusCondition status,
                int turns = USE_DEFAULT,
                const bool force = false
            );
            void faint();
            void bench();

            const std::set<MetaDefinition::VolatileStatusCondition>& getVolatileStatusSet() const;
            bool hasVolatileStatus(const MetaDefinition::VolatileStatusCondition status) const;
            void addVolatileStatus(const MetaDefinition::VolatileStatusCondition status, const int turns = USE_DEFAULT);
            void clearVolatileStatus(const MetaDefinition::VolatileStatusCondition status);
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
