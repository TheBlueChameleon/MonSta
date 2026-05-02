#ifndef STATUSCONDITION_HPP
#define STATUSCONDITION_HPP

#include <string_view>

namespace MetaDefinition
{
    constexpr auto POKEMON_STATUS_NORMAL    = "normal";

    // non volatile
    constexpr auto POKEMON_STATUS_PARALYZED = "paralyzed";
    constexpr auto POKEMON_STATUS_POISONED  = "poisoned";
    constexpr auto POKEMON_STATUS_ASLEEP    = "asleep";
    constexpr auto POKEMON_STATUS_BURNT     = "burnt";
    constexpr auto POKEMON_STATUS_FROZEN    = "frozen";
    constexpr auto POKEMON_STATUS_FAINTED   = "fainted";

    // volatile
    constexpr auto POKEMON_STATUS_FLINCHED  = "flinched";
    constexpr auto POKEMON_STATUS_CONFUSED  = "confused";
    constexpr auto POKEMON_STATUS_BADPOISON = "badlyPoisoned";
    constexpr auto POKEMON_STATUS_BOUND     = "bound";
    constexpr auto POKEMON_STATUS_SEEDED    = "seeded";

    enum class StatusCondition
    {
        NORMAL,
        PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED,
        FLINCHED, CONFUSED, BADLY_POISONED, BOUND, SEEDED
    };

    enum class NonVolatileStatusCondition { NORMAL, PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED };
    enum class VolatileStatusCondition { FLINCHED, CONFUSED, BADLY_POISONED, BOUND, SEEDED };

    StatusCondition getStatusConditionFromName(const std::string_view name);
    std::string_view getStatusConditionName(const StatusCondition status);

    NonVolatileStatusCondition  toNonVolatileStatusCondition(const StatusCondition status);
    VolatileStatusCondition     toVolatileStatusCondition(const StatusCondition status);

} // namespace SimulationMode

#endif // STATUSCONDITION_HPP
