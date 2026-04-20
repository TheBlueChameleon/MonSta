#ifndef TYPEINFO_HPP
#define TYPEINFO_HPP

#include <optional>
#include <string>

namespace SimulationMode
{
    static constexpr auto PHYSICAL = "physical";
    static constexpr auto SPECIAL  = "special";
    static constexpr auto STATUS   = "status";

    enum class MoveCategory {PHYSICAL, SPECIAL, STATUS};

    MoveCategory getMoveCategoryFromName(const std::string_view name);
    std::string_view getMoveCategoryName(const MoveCategory category);

    struct PokemonType
    {
        std::string                 primary;
        std::optional<std::string>  secondary;
    };

} // namespace SimulationMode

#endif // TYPEINFO_HPP
