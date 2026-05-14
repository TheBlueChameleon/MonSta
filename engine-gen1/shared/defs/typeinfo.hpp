#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <optional>
#include <string>

namespace MetaDefinition
{
    constexpr auto PHYSICAL = "physical";
    constexpr auto SPECIAL  = "special";
    constexpr auto STATUS   = "status";

    enum class MoveCategory {PHYSICAL, SPECIAL, STATUS};

    MoveCategory getMoveCategoryFromName(const std::string_view name);
    std::string_view getMoveCategoryName(const MoveCategory category);

    struct PokemonType
    {
        std::string                 primary;
        std::optional<std::string>  secondary;

        bool matches(const std::string_view other) const;
    };

} // namespace SimulationMode

#endif // TYPEINFO_HPP
