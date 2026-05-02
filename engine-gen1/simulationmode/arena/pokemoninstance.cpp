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
    int PokemonInstance::takeDirectDamage(const int amount)
    {
        const auto actualDamage = std::min(hp, amount);

        if (useRageCounter && actualDamage > 0)
        {
            ++rageCounter;
        }

        hp -= actualDamage;
        if (hp == 0)
        {
            faint();
        }

        setLastDamageReceived(actualDamage);
        return actualDamage;
    }

    int PokemonInstance::takeSubstituteDamage(const int amount)
    {
        const auto actualDamage = std::min(substituteHP, amount);
        setLastDamageReceived(actualDamage);

        substituteHP -= actualDamage;
        if (substituteHP == 0)
        {
            knockedOutSubstitute = true;
        }

        setLastDamageReceived(actualDamage);
        return actualDamage;
    }

    void PokemonInstance::setLastDamageReceived(const int amount)
    {
        lastDamageReceived = amount;
    }

    void PokemonInstance::recalculateStats()
    {

    }

    double PokemonInstance::getStageMultiplier(const int stage, const std::string_view stageName) const
    {
        switch (stage)
        {
            case  6:
                return .25;
            case  5:
                return .28;
            case  4:
                return .33;
            case  3:
                return .4;
            case  2:
                return .5;
            case  1:
                return .66;
            case  0:
                return 1.0;
            case -1:
                return 1.5;
            case -2:
                return 2.0;
            case -3:
                return 2.5;
            case -4:
                return 3.0;
            case -5:
                return 3.5;
            case -6:
                return 4.0;
        }

        throw IllegalStateError(std::format("Illegal {} stage: {}", stageName, stage));
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

    int PokemonInstance::takeDamage(const int amount)
    {
        if (substituteHP > 0)
        {
            return takeSubstituteDamage(amount);
        }
        else
        {
            return takeDirectDamage(amount);
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

        throw IllegalStateError("Unknow Stat ID: "s + std::to_string(static_cast<int>(stat)));
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

        throw IllegalStateError("Unknow Stat ID: "s + std::to_string(static_cast<int>(stat)));
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
        throw IllegalStateError("Unknow Stat Stage ID: "s + std::to_string(static_cast<int>(stat)));
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
        throw IllegalStateError("Unknow Stat Stage ID: "s + std::to_string(static_cast<int>(stat)));
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
                return getStageMultiplier(stageCritRate, STATSTAGE_CRITRATE);
        }
        throw IllegalStateError("Unknow Stat Stage ID: "s + std::to_string(static_cast<int>(stat)));
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

    void PokemonInstance::decreaseTurnCounts()
    {
        decreaseSleepCounter();
        decreseConfusionCounter();
        decreaseBoundCounter();
        decreaseSkipTurnCounter();
        decreaseLockedMoveCounter();
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
        }
        return nvStatus;
    }

    void PokemonInstance::faint()
    {
        nvStatus = NonVolatileStatusCondition::FAINTED;
        volatileStatus.clear();

        sleepCounter = 0;
        confusionCounter = 0;
        boundCounter = 0;
        toxicCounter = 0;
        rageCounter = 0;
        skipTurnCounter = 0;
        useRageCounter = false;
    }

    void PokemonInstance::bench()
    {
        volatileStatus.clear();
        confusionCounter = 0;
        boundCounter = 0;
        toxicCounter = 0;
        rageCounter = 0;
        skipTurnCounter = 0;
        useRageCounter = false;
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

    void PokemonInstance::clearTemporaryFlags()
    {
        knockedOutSubstitute = false;
        if (lockedMoveReleaseTurn)
        {
            semiInvulnerable = false;
        }
    }

} // namespace SimulationMode
