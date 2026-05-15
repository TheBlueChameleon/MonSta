#include <format>

#include <base/errors.hpp>

#include <services/rngservice.hpp>

#include "shared/registry/registry.hpp"

#include "damagecalculator.hpp"
#include "pokemoninstance.hpp"

using namespace MetaDefinition;
using namespace Registry;
using namespace std::string_literals;

namespace SimulationMode
{
    static void assertStageBetween(
        const int value, const int min, const int max,
        const std::string_view stageName
    )
    {
        constexpr auto messageTemplate = "Illegal {} Stage: {}";

        if ((value < min) || (value > max))
        {
            throw IllegalStateError(std::format(messageTemplate, stageName, value));
        }
    }

    static uint8_t getCritrollThresholdOriginal(const uint8_t baseSpeed, const bool highCritrateMove, const int stageCritRate)
    {
        if (highCritrateMove)
        {
            if (stageCritRate > 0)
            {
                return std::min(8 * (baseSpeed >> 1), 255);
            }
            else
            {
                return 4 * (baseSpeed >> 2);
            }
        }
        else
        {
            if (stageCritRate > 0)
            {
                return baseSpeed >> 3;
            }
            else
            {
                return baseSpeed >> 1;
            }
        }
    }

    static uint8_t getCritrollThresholdGlitchLess(const uint8_t baseSpeed, const bool highCritrateMove, const int stageCritRate)
    {
        if (highCritrateMove)
        {
            if (stageCritRate > 0)
            {
                return std::min(8 * (baseSpeed >> 1), 255);
            }
            else
            {
                return std::min(32 * (baseSpeed >> 1), 255);
            }
        }
        else
        {
            if (stageCritRate > 0)
            {
                return 4 * (baseSpeed >> 1);
            }
            else
            {
                return baseSpeed >> 1;
            }
        }
    }

    int PokemonInstance::takeDirectDamage(const int amount, const DamageKind damageKind)
    {
        const auto actualDamage = takeDamageShared(amount, damageKind, hp);

        if (hp == 0)
        {
            faint();
        }

        return actualDamage;
    }

    int PokemonInstance::takeSubstituteDamage(const int amount, const DamageKind damageKind)
    {
        const auto actualDamage = takeDamageShared(amount, damageKind, substituteHP);

        if (substituteHP == 0)
        {
            knockedOutSubstitute = true;
        }

        return actualDamage;
    }

    int PokemonInstance::takeDamageShared(const int amount, const DamageKind damageKind, int& counter)
    {
        const auto actualDamage = std::min(counter, amount);

        bool enableRage = false;
        bool rememberDamage = false;
        switch (damageKind)
        {
            case SimulationMode::PokemonInstance::DamageKind::DIRECT_ATTACK:
            case SimulationMode::PokemonInstance::DamageKind::CONFUSION:
                enableRage = true;
                rememberDamage = true;
                break;
            case SimulationMode::PokemonInstance::DamageKind::LEECH_SEED:
                rememberDamage = true;
                break;
            case SimulationMode::PokemonInstance::DamageKind::SELF_INFLICTED:
                enableRage = true;
                break;
            case SimulationMode::PokemonInstance::DamageKind::RESIDUAL:
                break;
        }

        // *INDENT-OFF*
        if (rememberDamage) { lastDamageReceived += actualDamage; }
        if (enableRage)     { changeStatStage(StatStage::ATK, actualDamage > 0); }
        // *INDENT-ON*

        counter -= actualDamage;
        return actualDamage;
    }

    int PokemonInstance::takeConfusionDamage()
    {
        DamageInfo di;
        di.level = level;
        di.power = mechanicsDefinition.confusionHitStrength;
        di.offense = atk;
        di.defense = def;
        // unboosted offense/defense irrelevant because no crits possible
        di.criticalHit = false;
        di.stabMultiplier = 1.0;
        di.typeMultiplier = 1.0;

        // TODO: opponent's reflect will act like a screen here...
        di.screen = false;

        const int damage = getDamageRoll(di);
        return takeDamage(damage, DamageKind::CONFUSION);
    }

    int PokemonInstance::takePoisonDamage()
    {
        const int damage = hpMax * mechanicsDefinition.poisonDamagePercentage;
        return takeDamage(damage, DamageKind::RESIDUAL);
    }

    int PokemonInstance::takeBadPoisonDamage()
    {
        const int damage = hpMax * mechanicsDefinition.poisonDamagePercentage * toxicCounter;
        return takeDamage(damage, DamageKind::RESIDUAL);
    }

    int PokemonInstance::takeBurnDamage()
    {
        const int damage = hpMax * mechanicsDefinition.burnDamagePercentage;
        return takeDamage(damage, DamageKind::RESIDUAL);
    }

    int PokemonInstance::takeSeedDamage()
    {
        int damage = hpMax * mechanicsDefinition.leechSeedPercentage;
        if (mechanicsDefinition.toxicLeechSeedGlitch)
        {
            damage *= std::min(1, toxicCounter);
        }
        lastSeedDamage = takeDamage(damage, DamageKind::LEECH_SEED);
        return lastSeedDamage;
    }

    void PokemonInstance::setKnockedOutSubstitute(bool value)
    {
        knockedOutSubstitute = value;
    }

    void PokemonInstance::recalculateStats()
    {
        // TODO
    }

    double PokemonInstance::getStageMultiplier(const int stage, const std::string_view stageName) const
    {
        // *INDENT-OFF*
        if (stage >= 0) { return (2.0 + stage) / 2.0; }
        else            { return 2.0 / (2.0 - stage); }
        // *INDENT-ON*
    }

    PokemonTypeID PokemonInstance::getTypeFromSpecies() const
    {
        return pokemonDatabase.getEntry(speciesData.species).typeID;
    }

    void PokemonInstance::setSleepCounter(int value)
    {
        if (sleepCounter == 0)
        {
            if (value == USE_DEFAULT)
            {
                value = RngService::getIntBetween(
                            mechanicsDefinition.sleepMinTurns,
                            mechanicsDefinition.sleepMaxTurns
                        );
            }
            else if (value < 0)
            {
                throw IllegalArgumentError("Cannot set sleep counter to a negative value");
            }
            sleepCounter = value;
        }
    }

    void PokemonInstance::decreaseSleepCounter()
    {
        if (sleepCounter > 0)
        {
            --sleepCounter;
            if (sleepCounter == 0)
            {
                setSkipTurnCounter(1);
            }
        }
    }

    void PokemonInstance::setConfusionCounter(int turns)
    {
        if (confusionCounter == 0)
        {
            if (turns == USE_DEFAULT)
            {
                turns = RngService::getIntBetween(
                            mechanicsDefinition.confusionMinTurns,
                            mechanicsDefinition.confusionMaxTurns
                        );
            }
            else if (turns < 0)
            {
                throw IllegalArgumentError("Cannot set confusion counter to a negative value");
            }
            confusionCounter = turns;
        }
    }

    void PokemonInstance::decreseConfusionCounter()
    {
        confusionCounter -= (confusionCounter > 0);
    }

    void PokemonInstance::setBoundCounter(const int turns)
    {
        if (boundCounter == 0)
        {
            if (turns < 0)
            {
                throw IllegalArgumentError("Cannot set bound counter to a negative value");
            }

            setEscapePrevented(true);
            boundCounter = turns;
        }
    }

    void PokemonInstance::decreaseBoundCounter()
    {
        if (boundCounter > 0)
        {
            --boundCounter;
            if (boundCounter == 0)
            {
                clearVolatileStatus(VolatileStatusCondition::BOUND);
                setEscapePrevented(false);
            }
        }
    }

    void PokemonInstance::decreaseSkipTurnCounter()
    {
        skipTurnCounter -= (skipTurnCounter > 0);
    }

    void PokemonInstance::decreaseLockedMoveCounter()
    {
        if (lockedMoveReleaseTurn)
        {
            lockedMoveReleaseTurn = false;
            return;
        }

        if (lockedMoveCounter == 0)
        {
            if (lockedMove != nullptr)
            {
                lockedMoveReleaseTurn = true;
                lockedMove = nullptr;
            }
            return;
        }

        --lockedMoveCounter;
    }

    void PokemonInstance::increaseToxicCounter()
    {
        toxicCounter += (toxicCounter < mechanicsDefinition.toxicCounterMax);
    }

    void PokemonInstance::clearPersistentFlags()
    {
        volatileStatus.clear();
        confusionCounter        = 0;
        boundCounter            = 0;
        toxicCounter            = 0;
        skipTurnCounter         = 0;
        useRageCounter          = false;
        protectCancelLockedMove = false;
        effectiveType           = getTypeFromSpecies();
    }

    void PokemonInstance::clearTemporaryFlags()
    {
        ignoreMoveType = false;
        highCritrateMove = false;
        knockedOutSubstitute = false;
        if (lockedMoveReleaseTurn)
        {
            semiInvulnerable = false;
        }
    }

    int PokemonInstance::takeDamage(const int amount, const DamageKind damageKind)
    {
        if (substituteHP > 0)
        {
            return takeSubstituteDamage(amount, damageKind);
        }
        else
        {
            return takeDirectDamage(amount, damageKind);
        }
    }

    int PokemonInstance::recoverHealth(const int amount)
    {
        const auto actualHP = std::min(amount, hpMax - hp);
        hp += actualHP;
        return actualHP;
    }

    int PokemonInstance::getLastDamageReceived() const
    {
        return lastDamageReceived;
    }

    int PokemonInstance::getAccumulatedDamage() const
    {
        return accumulatedDamage;
    }

    void PokemonInstance::addToAccumulatedDamage(const int amount)
    {
        accumulatedDamage += amount;
    }

    void PokemonInstance::resetAccumulatedDamage()
    {
        accumulatedDamage = 0;
    }

    int PokemonInstance::getSubstituteHP() const
    {
        return substituteHP;
    }

    void PokemonInstance::setSubstituteHP(const int value)
    {
        substituteHP = std::min(value, 1);
    }

    bool PokemonInstance::getKnockedOutSubstitute() const
    {
        return knockedOutSubstitute;
    }

    const PokemonDefinition& PokemonInstance::getSpeciesData() const
    {
        return speciesData;
    }

    int PokemonInstance::getLevel() const
    {
        return level;
    }

    int PokemonInstance::getStat(const Stat stat) const
    {
        switch (stat)
        {
            case MetaDefinition::Stat::HP:
                return hp;
            case MetaDefinition::Stat::ATK:
                return atk;
            case MetaDefinition::Stat::DEF:
                return def;
            case MetaDefinition::Stat::SPC:
                return spc;
            case MetaDefinition::Stat::SPD:
                return spd;
        }

        throw IllegalStateError(std::format("Unknow Stat ID: {}", static_cast<int>(stat)));
    }

    int PokemonInstance::getInitialStat(const MetaDefinition::Stat stat) const
    {
        switch (stat)
        {
            case MetaDefinition::Stat::HP:
                return hpMax;
            case MetaDefinition::Stat::ATK:
                return initialAtk;
            case MetaDefinition::Stat::DEF:
                return initialDef;
            case MetaDefinition::Stat::SPC:
                return initialSpc;
            case MetaDefinition::Stat::SPD:
                return initialSpd;
        }

        throw IllegalStateError(std::format("Unknow Stat ID: {}", static_cast<int>(stat)));
    }

    void PokemonInstance::setStat(const Stat stat, int value)
    {
        switch (stat)
        {
            case MetaDefinition::Stat::HP:
                hp = value;
                break;
            case MetaDefinition::Stat::ATK:
                atk = value;
                break;
            case MetaDefinition::Stat::DEF:
                def = value;
                break;
            case MetaDefinition::Stat::SPC:
                spc = value;
                break;
            case MetaDefinition::Stat::SPD:
                spd = value;
                break;
        }

        throw IllegalStateError(std::format("Unknow Stat ID: {}", static_cast<int>(stat)));
    }

    int PokemonInstance::getStatStage(const StatStage stat)
    {
        switch (stat)
        {
            case MetaDefinition::StatStage::ATK:
                return stageAtk;
            case MetaDefinition::StatStage::DEF:
                return stageDef;
            case MetaDefinition::StatStage::SPC:
                return stageSpc;
            case MetaDefinition::StatStage::SPD:
                return stageSpd;
            case MetaDefinition::StatStage::Accuracy:
                return stageAccuracy;
            case MetaDefinition::StatStage::Evasion:
                return stageEvasion;
            case MetaDefinition::StatStage::CritRate:
                return stageCritRate;
        }
        throw IllegalStateError(std::format("Unknow Stat Stage ID: {}", static_cast<int>(stat)));
    }

    void PokemonInstance::setStatStage(const StatStage stat, int value)
    {
        const auto stageMin = -mechanicsDefinition.statStageAbsMax;
        const auto stageMax = +mechanicsDefinition.statStageAbsMax;

        switch (stat)
        {
            case MetaDefinition::StatStage::ATK:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_ATK);
                stageAtk = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::DEF:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_DEF);
                stageDef = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::SPC:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_SPC);
                stageSpc = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::SPD:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_SPD);
                stageSpd = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::Accuracy:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_ACCURACY);
                stageAccuracy = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::Evasion:
                assertStageBetween(value, stageMin, stageMax, STATSTAGE_EVASION);
                stageEvasion = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::CritRate:
                assertStageBetween(value, -1, 1, STATSTAGE_CRITRATE);           // sic: only +/- 1 for CritRate
                stageCritRate = value;
                recalculateStats();
                break;
        }
        throw IllegalStateError(std::format("Unknow Stat Stage ID: {}", static_cast<int>(stat)));
    }

    void PokemonInstance::changeStatStage(const MetaDefinition::StatStage stat, int amount)
    {
        int stage = getStatStage(stat) + amount;

        if (stat == StatStage::CritRate)
        {
            // *INDENT-OFF*
            if (stage < -1) {stage = -1;}
            if (stage > +1) {stage = +1;}
            // *INDENT-ON*
        }
        else
        {
            // *INDENT-OFF*
            if (stage < -mechanicsDefinition.statStageAbsMax) {stage = -mechanicsDefinition.statStageAbsMax;}
            if (stage > +mechanicsDefinition.statStageAbsMax) {stage = +mechanicsDefinition.statStageAbsMax;}
            // *INDENT-ON*
        }
        setStatStage(stat, stage);
    }

    double PokemonInstance::getStageMultiplier(const StatStage stat) const
    {
        switch (stat)
        {
            case MetaDefinition::StatStage::ATK:
                return getStageMultiplier(stageAtk, STATSTAGE_ATK);
            case MetaDefinition::StatStage::DEF:
                return getStageMultiplier(stageDef, STATSTAGE_DEF);
            case MetaDefinition::StatStage::SPC:
                return getStageMultiplier(stageSpc, STATSTAGE_SPC);
            case MetaDefinition::StatStage::SPD:
                return getStageMultiplier(stageSpd, STATSTAGE_SPD);
            case MetaDefinition::StatStage::Accuracy:
                return getStageMultiplier(stageAccuracy, STATSTAGE_ACCURACY);
            case MetaDefinition::StatStage::Evasion:
                return getStageMultiplier(-stageEvasion, STATSTAGE_EVASION);
            case MetaDefinition::StatStage::CritRate:
                throw IllegalStateError("Attempt to get stage multiplier for critRate");
        }
        throw IllegalStateError(
            std::format("Unknow Stat Stage ID: {}", static_cast<int>(stat))
        );
    }

    uint8_t PokemonInstance::getCritRollThreshold() const
    {
        if (mechanicsDefinition.critRateGlitch)
        {
            return getCritrollThresholdOriginal(initialSpd, highCritrateMove, stageCritRate);
        }
        else
        {
            return getCritrollThresholdGlitchLess(initialSpd, highCritrateMove, stageCritRate);
        }
    }

    NonVolatileStatusCondition PokemonInstance::getNvStatus() const
    {
        return nvStatus;
    }

    NonVolatileStatusCondition PokemonInstance::setNvStatus(NonVolatileStatusCondition status, int turns, const bool force)
    {
        if (force || nvStatus == NonVolatileStatusCondition::NORMAL)
        {
            nvStatus = status;
            if (status == NonVolatileStatusCondition::ASLEEP)
            {
                setSleepCounter(turns);
            }
        }

        return nvStatus;
    }

    const std::unordered_set<VolatileStatusCondition>& PokemonInstance::getVolatileStatusSet() const
    {
        return volatileStatus;
    }

    bool PokemonInstance::hasVolatileStatus(const MetaDefinition::VolatileStatusCondition status) const
    {
        return volatileStatus.contains(status);
    }

    void PokemonInstance::addVolatileStatus(const VolatileStatusCondition status, const int turns)
    {
        const auto [_, inserted] = volatileStatus.insert(status);
        if (inserted)
        {
            switch (status)
            {
                case VolatileStatusCondition::FLINCHED:
                    cancelLockedMove();
                    setSkipTurnCounter(turns);
                    break;

                case MetaDefinition::VolatileStatusCondition::CONFUSED:
                    setConfusionCounter(turns);
                    break;

                case VolatileStatusCondition::BADLY_POISONED:
                    if (getNvStatus() != NonVolatileStatusCondition::POISONED)
                    {
                        setNvStatus(NonVolatileStatusCondition::POISONED, turns);
                    }
                    else
                    {
                        clearVolatileStatus(VolatileStatusCondition::BADLY_POISONED);
                    }
                    break;

                case MetaDefinition::VolatileStatusCondition::BOUND:
                    setBoundCounter(turns);
                    break;
                case MetaDefinition::VolatileStatusCondition::SEEDED:
                    break;
            }
        }
    }

    void PokemonInstance::clearVolatileStatus(const MetaDefinition::VolatileStatusCondition status)
    {
        volatileStatus.erase(status);
    }

    bool PokemonInstance::handleStatusPreMove()
    {
        switch (nvStatus)
        {
            case MetaDefinition::NonVolatileStatusCondition::NORMAL:
                break;
            case MetaDefinition::NonVolatileStatusCondition::PARALYZED:
                if (RngService::getRandomPercentage() < mechanicsDefinition.fullParalysisChance)
                {
                    return false;
                }
                break;
            case MetaDefinition::NonVolatileStatusCondition::POISONED:
                break;
            case MetaDefinition::NonVolatileStatusCondition::ASLEEP:
                return false;
            case MetaDefinition::NonVolatileStatusCondition::BURNT:
                break;
            case MetaDefinition::NonVolatileStatusCondition::FROZEN:
                return false;
            case MetaDefinition::NonVolatileStatusCondition::FAINTED:
                break;
        }

        if (hasVolatileStatus(VolatileStatusCondition::FLINCHED))
        {
            return false;
        }

        if (hasVolatileStatus(VolatileStatusCondition::CONFUSED))
        {
            takeConfusionDamage();
            return false;
        }

        if (hasVolatileStatus(VolatileStatusCondition::BOUND))
        {
            return false;
        }

        return true;
    }

    void PokemonInstance::handleStatusPostMove()
    {
        bool badToxicHandled = false;

        if (hasVolatileStatus(VolatileStatusCondition::BADLY_POISONED))
        {
            takeBadPoisonDamage();
            badToxicHandled = true;
        }

        if (hasVolatileStatus(VolatileStatusCondition::SEEDED))
        {
            takeSeedDamage();
        }

        switch (nvStatus)
        {
            case MetaDefinition::NonVolatileStatusCondition::NORMAL:
                break;
            case MetaDefinition::NonVolatileStatusCondition::PARALYZED:
                break;
            case MetaDefinition::NonVolatileStatusCondition::POISONED:
                if (!badToxicHandled)
                {
                    takePoisonDamage();
                }
                break;
            case MetaDefinition::NonVolatileStatusCondition::ASLEEP:
                break;
            case MetaDefinition::NonVolatileStatusCondition::BURNT:
                takeBurnDamage();
                break;
            case MetaDefinition::NonVolatileStatusCondition::FROZEN:
                break;
            case MetaDefinition::NonVolatileStatusCondition::FAINTED:
                faint();
                break;
        }
    }

    bool PokemonInstance::isEscapePrevented() const
    {
        return preventEscape;
    }

    void PokemonInstance::setEscapePrevented(const bool value)
    {
        preventEscape = value;
    }

    bool PokemonInstance::isSemiInvulnerable() const
    {
        return semiInvulnerable;
    }

    void PokemonInstance::setSemiInvulnerable(const bool value)
    {
        semiInvulnerable = value;
    }

    int PokemonInstance::getSkipTurnCounter() const
    {
        return skipTurnCounter;
    }

    void PokemonInstance::setSkipTurnCounter(const int turns)
    {
        if (skipTurnCounter == 0)
        {
            skipTurnCounter = turns;
        }
    }

    bool PokemonInstance::getIgnoreMoveType() const
    {
        return ignoreMoveType;
    }

    void PokemonInstance::setIgnoreMoveType(bool value)
    {
        ignoreMoveType = value;
    }

    int PokemonInstance::getSleepCounter() const
    {
        return sleepCounter;
    }

    int PokemonInstance::getBoundCounter() const
    {
        return boundCounter;
    }

    int PokemonInstance::getConfusionCounter() const
    {
        return confusionCounter;
    }

    bool PokemonInstance::getHighCritrateMove() const
    {
        return highCritrateMove;
    }

    void PokemonInstance::setHighCritrateMove(bool value)
    {
        highCritrateMove = value;
    }

    std::optional<MetaDefinition::MoveCategory> PokemonInstance::getScreen() const
    {
        return screen;
    }

    void PokemonInstance::setScreen(MetaDefinition::MoveCategory newScreen)
    {
        screen = newScreen;
    }

    void PokemonInstance::clearScreen()
    {
        screen.reset();
    }

    MetaDefinition::PokemonTypeID PokemonInstance::getEffectiveTypeID() const
    {
        return effectiveType;
    }

    void PokemonInstance::setEffectiveTypeID(const PokemonTypeID& value)
    {
        effectiveType = value;
    }

    const Move* const PokemonInstance::getSelectedMove() const
    {
        return selectedMove;
    }

    const Move* const PokemonInstance::getLockedMove() const
    {
        return lockedMove;
    }

    bool PokemonInstance::getProtectCancelLockedMove() const
    {
        return protectCancelLockedMove;
    }

    int PokemonInstance::getLockedMoveCounter() const
    {
        return lockedMoveCounter;
    }

    bool PokemonInstance::isLockedMoveReleaseTurn() const
    {
        return lockedMoveReleaseTurn;
    }

    void PokemonInstance::lockMove(
        const Move* const move,
        const int turns,
        const bool protectCancel
    )
    {
        if (getLockedMoveCounter() == 0)
        {
            lockedMove = move;
            lockedMoveCounter = turns;
            lockedMoveReleaseTurn = false;
            protectCancelLockedMove = protectCancel;
        }
    }

    void PokemonInstance::cancelLockedMove()
    {
        if (!protectCancelLockedMove)
        {
            selectedMove = nullptr;
            lockedMove = nullptr;
            lockedMoveCounter = 0;
            lockedMoveReleaseTurn = false;
            protectCancelLockedMove = false;
        }
    }

    bool PokemonInstance::canChooseMove() const
    {
        return (getLockedMoveCounter() == 0) &&
               (getSkipTurnCounter() == 0) &&
               (getBoundCounter() == 0);
    }

    void PokemonInstance::faint()
    {
        hp            = 0;
        substituteHP  = 0;
        stageAtk      = 0;
        stageDef      = 0;
        stageSpc      = 0;
        stageSpd      = 0;
        stageAccuracy = 0;
        stageEvasion  = 0;
        stageCritRate = 0;
        nvStatus = NonVolatileStatusCondition::FAINTED;
        clearPersistentFlags();
        recalculateStats();
    }

    void PokemonInstance::bench()
    {
        clearTemporaryFlags();
        clearPersistentFlags();
    }

    void PokemonInstance::decreaseTurnCounts()
    {
        decreaseSleepCounter();
        decreseConfusionCounter();
        decreaseBoundCounter();
        decreaseSkipTurnCounter();
        decreaseLockedMoveCounter();
    }

    bool PokemonInstance::newTurnHook()
    {
        lastDamageReceived = 0;
        bool canMoveAfter = true;

        canMoveAfter &= handleStatusPreMove();
        canMoveAfter &= (skipTurnCounter == 0);
        canMoveAfter &= (boundCounter == 0);

        return canMoveAfter;
    }

    void PokemonInstance::endTurnHook()
    {
        clearTemporaryFlags();
        handleStatusPostMove();
        decreaseTurnCounts();
    }

} // namespace SimulationMode
