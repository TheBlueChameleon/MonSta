#ifndef TEAMDEFINITION_HPP
#define TEAMDEFINITION_HPP

#include <string>
#include <vector>

#include "pokemondefition.hpp"

namespace MetaDefinition
{
    struct TeamDefinition
    {
        std::string name;
        int obedienceCap;

        bool expAll;
        bool badgeBoost_ATK;
        bool badgeBoost_DEF;
        bool badgeBoost_SPC;
        bool badgeBoost_SPD;
        bool statMoveDebuf;
        bool usePP;

        std::vector<std::string>       items;
        std::vector<PokemonDefinition> pokemon;
    };
}

#endif // TEAMDEFINITION_HPP
