#ifndef POKEMONSTATUS_HPP
#define POKEMONSTATUS_HPP

#include <string_view>

namespace SimulationMode
{
    enum class PokemonStatus { NORMAL, PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED };

    PokemonStatus getStatusFromName(const std::string_view name);
    std::string_view getPokemonStatusName(const PokemonStatus status);

} // namespace SimulationMode

#endif // POKEMONSTATUS_HPP
