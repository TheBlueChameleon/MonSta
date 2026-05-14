#ifndef POKEMONINSTANCE_HPP
#define POKEMONINSTANCE_HPP

#include <cinttypes>
#include <limits>
#include <optional>
#include <unordered_set>

#include "shared/defs/pokemondefition.hpp"
#include "shared/defs/stat.hpp"
#include "shared/defs/statstage.hpp"
#include "shared/defs/statuscondition.hpp"
#include "shared/defs/typeinfo.hpp"

#include "shared/registry/moves/move.hpp"
#include "shared/registry/typechart.hpp"

namespace SimulationMode
{
    class PokemonInstance
    {
        public:
            static constexpr auto USE_DEFAULT = -1;
            static constexpr auto FOREVER = std::numeric_limits<int>::max();

            enum class DamageKind { DIRECT_ATTACK, RESIDUAL, LEECH_SEED, CONFUSION, SELF_INFLICTED };

        private:
            MetaDefinition::PokemonDefinition speciesData;
            MetaDefinition::PokemonTypeID     effectiveType;
            int  level;

            int  hp;
            int  hpMax;
            int  substituteHP;
            bool knockedOutSubstitute;
            int  lastDamageReceived;
            int  lastSeedDamage;
            int  accumulatedDamage;

            int atk;
            int def;
            int spc;
            int spd;

            int initialAtk;
            int initialDef;
            int initialSpc;
            int initialSpd;

            int stageAtk;
            int stageDef;
            int stageSpc;
            int stageSpd;
            int stageAccuracy;
            int stageEvasion;
            int stageCritRate;

            MetaDefinition::NonVolatileStatusCondition nvStatus;
            std::unordered_set<MetaDefinition::VolatileStatusCondition> volatileStatus;

            bool highCritrateMove;
            bool preventEscape;
            bool semiInvulnerable;
            bool useRageCounter;
            int  skipTurnCounter;
            int  sleepCounter;
            int  confusionCounter;
            int  boundCounter;
            int  toxicCounter;
            std::optional<MetaDefinition::MoveCategory> screen;

            bool ignoreMoveType;
            bool protectCancelLockedMove;
            bool lockedMoveReleaseTurn;
            int  lockedMoveCounter;
            const MetaDefinition::Move* lockedMove;
            const MetaDefinition::Move* selectedMove;

        private:
            int  takeDirectDamage(const int amount, const DamageKind damageKind);
            int  takeSubstituteDamage(const int amount, const DamageKind damageKind);
            int  takeDamageShared(const int amount, const DamageKind damageKind, int& counter);
            int  takeConfusionDamage();
            int  takePoisonDamage();
            int  takeBadPoisonDamage();
            int  takeBurnDamage();
            int  takeSeedDamage();
            void setKnockedOutSubstitute(bool value);

            void   recalculateStats();
            double getStageMultiplier(const int stage, const std::string_view stageName) const;
            MetaDefinition::PokemonTypeID getTypeFromSpecies() const;

            void setSleepCounter(int value);
            void decreaseSleepCounter();
            void setConfusionCounter(const int turns);
            void decreseConfusionCounter();
            void setBoundCounter(const int turns);
            void decreaseBoundCounter();
            void decreaseSkipTurnCounter();
            void decreaseLockedMoveCounter();
            void increaseToxicCounter();

            void clearPersistentFlags();
            void clearTemporaryFlags();

        public:
            PokemonInstance() = default;

            // .............................................................. //
            // HP related

            int takeDamage(const int amount, const DamageKind damageKind = DamageKind::DIRECT_ATTACK);
            int recoverHealth(const int amount);
            int getLastDamageReceived() const;

            int  getAccumulatedDamage() const;
            void addToAccumulatedDamage(const int amount);
            void resetAccumulatedDamage();

            int  getSubstituteHP() const;
            void setSubstituteHP(const int value);
            bool getKnockedOutSubstitute() const;

            // .............................................................. //
            // stat and stage related

            const MetaDefinition::PokemonDefinition& getSpeciesData() const;
            int getLevel() const;

            int  getStat(const MetaDefinition::Stat stat) const;
            int  getInitialStat(const MetaDefinition::Stat stat) const;
            void setStat(const MetaDefinition::Stat stat, int value);

            int  getStatStage(const MetaDefinition::StatStage stat);
            void setStatStage(const MetaDefinition::StatStage stat, int value);
            void changeStatStage(const MetaDefinition::StatStage stat, int amount);

            double getStageMultiplier(const MetaDefinition::StatStage stat) const;
            uint8_t getCritRollThreshold() const;

            // .............................................................. //
            // status related

            MetaDefinition::NonVolatileStatusCondition getNvStatus() const;
            MetaDefinition::NonVolatileStatusCondition setNvStatus(
                MetaDefinition::NonVolatileStatusCondition status,
                int turns = USE_DEFAULT,
                const bool force = false
            );

            const std::unordered_set<MetaDefinition::VolatileStatusCondition>& getVolatileStatusSet() const;
            bool hasVolatileStatus(const MetaDefinition::VolatileStatusCondition status) const;
            void addVolatileStatus(const MetaDefinition::VolatileStatusCondition status, const int turns = USE_DEFAULT);
            void clearVolatileStatus(const MetaDefinition::VolatileStatusCondition status);

            bool handleStatusPreMove();
            void handleStatusPostMove();

            // .............................................................. //
            // flag and counter related

            bool isEscapePrevented() const;
            void setEscapePrevented(const bool value);

            bool isSemiInvulnerable() const;
            void setSemiInvulnerable(const bool value);

            int  getSkipTurnCounter() const;
            void setSkipTurnCounter(const int turns);

            bool getIgnoreMoveType() const;
            void setIgnoreMoveType(bool value);

            int getSleepCounter() const;
            int getBoundCounter() const;
            int getConfusionCounter() const;

            bool getHighCritrateMove() const;
            void setHighCritrateMove(bool value);

            std::optional<MetaDefinition::MoveCategory> getScreen() const;
            void setScreen(MetaDefinition::MoveCategory value);
            void clearScreen();

            MetaDefinition::PokemonTypeID getEffectiveTypeID() const;
            void setEffectiveTypeID(const MetaDefinition::PokemonTypeID& value);

            // .............................................................. //
            // multi-turn moves related

            const MetaDefinition::Move* const getSelectedMove() const;
            const MetaDefinition::Move* const getLockedMove() const;
            bool getProtectCancelLockedMove() const;
            int  getLockedMoveCounter() const;
            bool isLockedMoveReleaseTurn() const;
            void lockMove(const MetaDefinition::Move* const move, const int turns, const bool protectCancel = false);
            void cancelLockedMove();
            bool canChooseMove() const;

            // .............................................................. //
            // inter turn related

            void faint();
            void bench();

            void decreaseTurnCounts();
            bool newTurnHook();
            void endTurnHook();
    };

} // namespace SimulationMode

#endif // POKEMONINSTANCE_HPP
