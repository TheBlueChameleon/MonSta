#ifndef POKEMONSTATUS_HPP
#define POKEMONSTATUS_HPP

#include <string_view>

namespace SimulationMode
{
    static constexpr auto POKEMON_STATUS_NORMAL    = "normal";
    static constexpr auto POKEMON_STATUS_PARALYZED = "paralyzed";
    static constexpr auto POKEMON_STATUS_POISONED  = "poisoned";
    static constexpr auto POKEMON_STATUS_ASLEEP    = "asleep";
    static constexpr auto POKEMON_STATUS_BURNT     = "burnt";
    static constexpr auto POKEMON_STATUS_FROZEN    = "frozen";
    static constexpr auto POKEMON_STATUS_FAINTED   = "fainted";

    enum class PokemonStatus { NORMAL, PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED };

    PokemonStatus getStatusFromName(const std::string_view name);
    std::string_view getPokemonStatusName(const PokemonStatus status);

} // namespace SimulationMode

#endif // POKEMONSTATUS_HPP
