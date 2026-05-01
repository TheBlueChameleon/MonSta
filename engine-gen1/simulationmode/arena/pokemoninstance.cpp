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

    int PokemonInstance::getLastDamageReceived() const
    {
        return 0;
    }

    void PokemonInstance::setLastDamageReceived(const int amount)
    {

    }

    int PokemonInstance::getSkipTurnCount() const
    {
        return 0;
    }

    void PokemonInstance::reduceSkipTurnCount()
    {

    }

    void PokemonInstance::setSkipTurnCount(const int amount)
    {

    }

    const MetaDefinition::Move* const PokemonInstance::getCurrentMove() const
    {
        return nullptr;
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

    bool PokemonInstance::isTrapped() const
    {
        return false;
    }

    void PokemonInstance::setTrapped(bool value)
    {

    }

    void PokemonInstance::increaseRageCount()
    {

    }

    void PokemonInstance::decreaseTurnCounts()
    {
        reduceSkipTurnCount();
        decreaseLockNextMoveCount();
    }

} // namespace SimulationMode
