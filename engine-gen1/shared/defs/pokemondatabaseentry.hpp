#ifndef POKEMONDATABASEENTRY_HPP
#define POKEMONDATABASEENTRY_HPP

#include "experiencegroup.hpp"
#include "typeinfo.hpp"

namespace MetaDefinition
{
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
