#ifndef POKEMONDATABASEENTRY_HPP
#define POKEMONDATABASEENTRY_HPP

#include <string>

#include "typeinfo.hpp"

namespace MetaDefinition
{
    static constexpr auto FAST        = "Fast";
    static constexpr auto MEDIUM_FAST = "Medium Fast";
    static constexpr auto MEDIUM_SLOW = "Medium Slow";
    static constexpr auto SLOW        = "Slow";

    enum class ExperienceGroup { FAST, MEDIUM_FAST, MEDIUM_SLOW, SLOW };

    ExperienceGroup getExperienceGroupFromName(const std::string_view name);
    std::string_view getExperienceGroupName(const ExperienceGroup experienceGroup);

    struct PokemonDatabaseEntry
    {
        int             HP;
        int             ATK;
        int             DEF;
        int             SPC;
        int             SPD;
        PokemonType     type;
        int             expYield;
        ExperienceGroup expGroup;
    };

} // namespace SimulationMode

#endif // POKEMONDATABASEENTRY_HPP
