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

    int PokemonInstance::getStat(const Stat stat) const
    {
        return 1;
    }

    void PokemonInstance::setStat(const Stat stat, int value)
    {

    }

    int PokemonInstance::getStatStage(const StatStage)
    {
        return 0;
    }

    void PokemonInstance::setStatStage(const StatStage stat, int value)
    {

    }

    void PokemonInstance::changeStatStage(const StatStage stat, int amount)
    {

    }

} // namespace SimulationMode
