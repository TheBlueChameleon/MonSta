#include <format>

#include <base/errors.hpp>

#include <services/rngservice.hpp>

#include "shared/registry/registry.hpp"

#include "pokemoninstance.hpp"

using namespace MetaDefinition;
using namespace Registry;
using namespace std::string_literals;

namespace SimulationMode
{
    int PokemonInstance::takeDirectDamage(const int amount, const bool rageEnabled, const bool fromAttack)
    {
        const auto actualDamage = std::min(hp, amount);

        if (fromAttack)
        {
            if (useRageCounter && rageEnabled && actualDamage > 0)
            {
                changeStatStage(StatStage::ATK, +1);
            }
            lastDamageReceived = amount;
        }

        hp -= actualDamage;
        if (hp == 0)
        {
            faint();
        }

        return actualDamage;
    }

    int PokemonInstance::takeSubstituteDamage(const int amount, const bool fromAttack)
    {
        const auto actualDamage = std::min(substituteHP, amount);

        if (fromAttack)
        {
            lastDamageReceived = amount;
        }

        substituteHP -= actualDamage;
        if (substituteHP == 0)
        {
            knockedOutSubstitute = true;
        }

        return actualDamage;
    }

    int PokemonInstance::takeConfusionDamage()
    {
        const int damage = 0;       // TODO: full damage formula...
        return takeDamage(std::min(1, damage), false);
    }

    int PokemonInstance::takePoisonDamage()
    {
        const int damage = hpMax * mechanicsDefinition.poisonDamagePercentage;
        return takeDamage(std::min(1, damage), false);
    }

    int PokemonInstance::takeBadPoisonDamage()
    {
        const int damage = hpMax * mechanicsDefinition.poisonDamagePercentage * toxicCounter;
        return takeDamage(std::min(1, damage), false);
    }

    int PokemonInstance::takeBurnDamage()
    {
        const int damage = hpMax * mechanicsDefinition.burnDamagePercentage;
        return takeDamage(std::min(1, damage), false);
    }

    void PokemonInstance::recalculateStats()
    {
        // TODO
    }

    double PokemonInstance::getStageMultiplier(const int stage, const std::string_view stageName) const
    {
        const std::unordered_map<int, double> multipliers =
        {
            {-1, 0.66}, {-2, 0.50}, {-3, 0.40}, {-4, 0.33}, {-5, 0.28}, {-6, 0.25},
            { 0, 1.00},
            { 1, 1.50}, { 2, 2.00}, { 3, 2.50}, { 4, 3.00}, { 5, 3.50}, { 6, 4.00},
        };

        const auto it = multipliers.find(stage);
        // *INDENT-OFF*
        if (it == multipliers.end()) { throw IllegalStateError(std::format("Illegal {} stage: {}", stageName, stage)); }
        else                         { return it->second; }
        // *INDENT-ON*
    }

    void PokemonInstance::setSubstituteHP(const int value)
    {
        substituteHP = std::min(value, 1);
    }

    void PokemonInstance::setKnockedOutSubstitute(bool value)
    {
        knockedOutSubstitute = value;
    }

    void PokemonInstance::setSleepCounter(int value)
    {
        if (value == USE_DEFAULT)
        {
            value = RngService::getIntBetween(
                        mechanicsDefinition.sleepMinTurns,
                        mechanicsDefinition.sleepMaxTurns
                    );
        }
        sleepCounter = value;
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
        if (turns == USE_DEFAULT)
        {
            turns = RngService::getIntBetween(
                        mechanicsDefinition.confusionMinTurns,
                        mechanicsDefinition.confusionMaxTurns
                    );
        }
        confusionCounter = turns;
    }

    void PokemonInstance::decreseConfusionCounter()
    {
        confusionCounter -= (confusionCounter > 0);
    }

    void PokemonInstance::setBoundCounter(const int turns)
    {
        if (turns == USE_DEFAULT)
        {
            throw IllegalStateError("Cannot set bound counter to DEFAULT");
        }

        setEscapePrevented(true);
        setSkipTurnCounter(turns);
        boundCounter = turns;
    }

    void PokemonInstance::decreaseBoundCounter()
    {
        if (boundCounter > 0)
        {
            --boundCounter;
            if (boundCounter == 0)
            {
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
        if (lockedMoveCounter == 0)
        {
            if (lockedMove != nullptr)
            {
                lockedMoveReleaseTurn = true;
            }
            return;
        }

        if (lockedMoveReleaseTurn)
        {
            lockedMove = nullptr;
            lockedMoveReleaseTurn = false;
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
    }

    void PokemonInstance::clearTemporaryFlags()
    {
        knockedOutSubstitute = false;
        if (lockedMoveReleaseTurn)
        {
            semiInvulnerable = false;
        }
    }

    int PokemonInstance::takeDamage(const int amount, const bool applyRage, const bool fromAttack)
    {
        if (substituteHP > 0)
        {
            return takeSubstituteDamage(amount, fromAttack);
        }
        else
        {
            return takeDirectDamage(amount, applyRage, fromAttack);
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

    int PokemonInstance::getSubstituteHP() const
    {
        return substituteHP;
    }

    bool PokemonInstance::getKnockedOutSubstitute() const
    {
        return knockedOutSubstitute;
    }

    void PokemonInstance::installSubstitute(const int substituteHp)
    {
        if (substituteHp > hp)
        {
            return;
        }

        hp -= substituteHp;
        setSubstituteHP(substituteHp);
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
        switch (stat)
        {
            case MetaDefinition::StatStage::ATK:
                assertStageBetween(value, -6, 6, STATSTAGE_ATK);
                stageAtk = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::DEF:
                assertStageBetween(value, -6, 6, STATSTAGE_DEF);
                stageDef = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::SPC:
                assertStageBetween(value, -6, 6, STATSTAGE_SPC);
                stageSpc = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::SPD:
                assertStageBetween(value, -6, 6, STATSTAGE_SPD);
                stageSpd = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::Accuracy:
                assertStageBetween(value, -6, 6, STATSTAGE_ACCURACY);
                stageAccuracy = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::Evasion:
                assertStageBetween(value, -6, 6, STATSTAGE_EVASION);
                stageEvasion = value;
                recalculateStats();
                break;
            case MetaDefinition::StatStage::CritRate:
                assertStageBetween(value, -1, 1, STATSTAGE_CRITRATE);
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
            if (stage < -6) {stage = -6;}
            if (stage > +6) {stage = +6;}
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
                // *INDENT-OFF*
                if      (stageCritRate ==  0) { return 1.00; }
                else if (stageCritRate ==  1) { return 4.00; }
                else if (stageCritRate == -1) { return 0.25; }
                // *INDENT-ON*
        }
        throw IllegalStateError(
            std::format("Unknow Stat Stage ID: {}", static_cast<int>(stat))
        );
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

    const std::set<VolatileStatusCondition>& PokemonInstance::getVolatileStatusSet() const
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
                case MetaDefinition::VolatileStatusCondition::FLINCHED:
                    if (!getProtectCancelLockedMove())
                    {
                        selectedMove = nullptr;
                        cancelLockedMove();
                    }
                    if (getSkipTurnCounter() == 0)
                    {
                        setSkipTurnCounter(turns);
                    }
                    break;

                case MetaDefinition::VolatileStatusCondition::CONFUSED:
                    setConfusionCounter(turns);
                    break;

                case VolatileStatusCondition::BADLY_POISONED:
                    if (setNvStatus(NonVolatileStatusCondition::POISONED, turns) != NonVolatileStatusCondition::POISONED)
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

    bool PokemonInstance::handleStatus()
    {
        bool mayAttackAfter = true;
        bool badToxicHandled = false;

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
                takeBurnDamage();
                break;
            case MetaDefinition::NonVolatileStatusCondition::FROZEN:
                break;
            case MetaDefinition::NonVolatileStatusCondition::FAINTED:
                faint();
                break;
        }

        return mayAttackAfter;
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
        if (getLockedMoveCounter() == 0 && !isLockedMoveReleaseTurn())
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
            lockedMove = nullptr;
            lockedMoveCounter = 0;
            lockedMoveReleaseTurn = false;
            protectCancelLockedMove = false;
        }
    }

    bool PokemonInstance::canChooseMove() const
    {
        return !((isLockedMoveReleaseTurn()) || (getLockedMoveCounter() > 0));
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
    }

    void PokemonInstance::bench()
    {
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

} // namespace SimulationMode
