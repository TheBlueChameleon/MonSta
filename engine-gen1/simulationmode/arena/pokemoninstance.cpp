#include <base/errors.hpp>

#include <services/rngservice.hpp>

#include "shared/registry/registry.hpp"

#include "pokemoninstance.hpp"

using namespace MetaDefinition;
using namespace Registry;

namespace SimulationMode
{
    int PokemonInstance::takeDirectDamage(const int amount)
    {
        const auto actualDamage = std::min(hp, amount);
        setLastDamageReceived(actualDamage);

        if (useRageCounter && actualDamage > 0)
        {
            ++rageCounter;
        }

        hp -= actualDamage;
        if (hp == 0)
        {
            faint();
        }
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

    void PokemonInstance::faint()
    {
        nvStatus = NonVolatileStatusCondition::FAINTED;
        volatileStatus.clear();
        sleepCounter;

        confusionCounter = 0;
        boundCounter = 0;
        toxicCounter = 0;
        rageCounter = 0;
        skipTurnCounter = 0;
        useRageCounter = false;
        seeded = false;
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
                setSkipTurnCount(1);
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
        if (confusionCounter > 0)
        {
            --confusionCounter;
        }
    }

    void PokemonInstance::setBoundCounter(const int turns)
    {
        if (turns == USE_DEFAULT)
        {
            throw IllegalStateError("Cannot set bound counter to DEFAULT");
        }

        setEscapePrevented(true);
        setSkipTurnCount(turns);
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

    void PokemonInstance::decreaseLockNextMoveCounter()
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
        return 1;
    }

    void PokemonInstance::setStat(const Stat stat, int value)
    {

    }

    int PokemonInstance::getStatStage(const StatStage stat)
    {
        return 0;
    }

    void PokemonInstance::setStatStage(const StatStage stat, int value)
    {

    }

    void PokemonInstance::changeStatStage(const StatStage stat, int amount)
    {

    }

    double PokemonInstance::getHitChance()
    {
        return 0;
    }

    double PokemonInstance::getStrikeChance(const Move& move)
    {
        return 0;
    }

    bool PokemonInstance::isEscapePrevented() const
    {
        return false;
    }

    void PokemonInstance::setEscapePrevented(const bool value)
    {

    }

    bool PokemonInstance::isSemiInvulnerable() const
    {
        return false;
    }

    void PokemonInstance::setSemiInvulnerable(const bool value)
    {

    }

    int PokemonInstance::getSubstituteHP() const
    {
        return substituteHP;
    }

    void PokemonInstance::setSubstituteHP(int value)
    {
        substituteHP = value;
    }

    bool PokemonInstance::getKnockedOutSubstitute() const
    {
        return knockedOutSubstitute;
    }

    void PokemonInstance::setKnockedOutSubstitute(bool value)
    {
        knockedOutSubstitute = value;
    }

    int PokemonInstance::getSkipTurnCount() const
    {
        return 0;
    }

    void PokemonInstance::setSkipTurnCount(const int amount)
    {

    }

    void PokemonInstance::decreaseSkipTurnCount()
    {

    }

    int PokemonInstance::getSleepCounter() const
    {
        return 0;
    }

    int PokemonInstance::getBoundCounter() const
    {
        return 0;
    }

    int PokemonInstance::getConfusionCounter() const
    {
        return 0;
    }

    const Move* const PokemonInstance::getCurrentMove() const
    {
        return nullptr;
    }

    const Move* const PokemonInstance::getLockedMove() const
    {
        return nullptr;
    }

    bool PokemonInstance::getProtectCancelLockedMove() const
    {
        return protectCancelLockedMove;
    }

    int PokemonInstance::getLockedMoveCounter() const
    {
        return 0;
    }

    bool PokemonInstance::getLockedMoveReleaseTurn() const
    {
        return lockedMoveReleaseTurn;
    }

    void PokemonInstance::lockMove(
        const Move* const move,
        const int turns,
        const bool protectCancel
    )
    {
        if (getLockedMoveCounter() == 0 && !getLockedMoveReleaseTurn())
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
        return !((getLockedMoveReleaseTurn()) || (getLockedMoveCounter() > 0));
    }

    int PokemonInstance::getAccumulatedDamage() const
    {
        return 0;
    }

    void PokemonInstance::addToAccumulatedDamage(const int amount)
    {

    }

    void PokemonInstance::resetAccumulatedDamage()
    {

    }

    void PokemonInstance::decreaseTurnCounts()
    {
        decreaseSkipTurnCount();
        decreaseLockNextMoveCounter();
        decreaseBoundCounter();
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
                    if (getSkipTurnCount() == 0)
                    {
                        setSkipTurnCount(turns);
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
    }

} // namespace SimulationMode
