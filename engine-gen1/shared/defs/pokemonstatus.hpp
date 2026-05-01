#ifndef POKEMONSTATUS_HPP
#define POKEMONSTATUS_HPP

#include <string_view>

namespace MetaDefinition
{
    constexpr auto POKEMON_STATUS_NORMAL    = "normal";
    constexpr auto POKEMON_STATUS_PARALYZED = "paralyzed";
    constexpr auto POKEMON_STATUS_POISONED  = "poisoned";
    constexpr auto POKEMON_STATUS_ASLEEP    = "asleep";
    constexpr auto POKEMON_STATUS_BURNT     = "burnt";
    constexpr auto POKEMON_STATUS_FROZEN    = "frozen";
    constexpr auto POKEMON_STATUS_FAINTED   = "fainted";

    enum class PokemonStatus { NORMAL, PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED };

    PokemonStatus getPokemonStatusFromName(const std::string_view name);
    std::string_view getPokemonStatusName(const PokemonStatus status);

} // namespace SimulationMode

#endif // POKEMONSTATUS_HPP
