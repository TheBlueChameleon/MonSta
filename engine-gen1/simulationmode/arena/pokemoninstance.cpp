#include "pokemoninstance.hpp"

namespace SimulationMode
{
    PokemonInstance::PokemonInstance() {}

    int PokemonInstance::takeDamage(const int amount)
    {
        return 1;
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

} // namespace SimulationMode
