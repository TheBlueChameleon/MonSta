#include "pokemoninstance.hpp"

namespace SimulationMode
{
    PokemonInstance::PokemonInstance() {}

    int PokemonInstance::takeDamage(const int amount)
    {
        const auto actualDamage = 1;
        setLastDamageReceived(actualDamage);
        return actualDamage;
    }

    int PokemonInstance::recoverHealth(const int amount)
    {
        return 1;
    }

    int PokemonInstance::getLastDamageReceived() const
    {
        return 0;
    }

    void PokemonInstance::setLastDamageReceived(const int amount)
    {

    }

    int PokemonInstance::getStat(const MetaDefinition::Stat stat) const
    {
        return 1;
    }

    void PokemonInstance::setStat(const MetaDefinition::Stat stat, int value)
    {

    }

    int PokemonInstance::getStatStage(const MetaDefinition::StatStage stat)
    {
        return 0;
    }

    void PokemonInstance::setStatStage(const MetaDefinition::StatStage stat, int value)
    {

    }

    void PokemonInstance::changeStatStage(const MetaDefinition::StatStage stat, int amount)
    {

    }

    double PokemonInstance::getHitChance()
    {
        return 0;
    }

    double PokemonInstance::getStrikeChance()
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

    int PokemonInstance::getSleepCount() const
    {
        return 0;
    }

    void PokemonInstance::setSleepCount(const int value)
    {

    }

    void PokemonInstance::decreaseSleepCount()
    {

    }

    const MetaDefinition::Move* const PokemonInstance::getCurrentMove() const
    {
        return nullptr;
    }

    const MetaDefinition::Move* const PokemonInstance::getLockedInMove() const
    {
        return nullptr;
    }

    int PokemonInstance::getLockInCount() const
    {
        return 0;
    }

    void PokemonInstance::lockNextMove(const MetaDefinition::Move* const move, const int turns)
    {

    }

    void PokemonInstance::decreaseLockNextMoveCount()
    {

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

    int PokemonInstance::getBoundCount() const
    {
        return 0;
    }

    void PokemonInstance::setBoundCount(const int value)
    {
        setEscapePrevented(true);
    }

    void PokemonInstance::decreaseBoundCount()
    {
        // release EscapePrevented on drop to 0
    }

    void PokemonInstance::increaseRageCount()
    {

    }

    void PokemonInstance::decreaseTurnCounts()
    {
        decreaseSkipTurnCount();
        decreaseLockNextMoveCount();
        decreaseBoundCount();
    }

} // namespace SimulationMode
