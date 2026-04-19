#ifndef POKEMONDEFITION_HPP
#define POKEMONDEFITION_HPP

#include <string>

#include "pokemonstatus.hpp"

namespace SimulationMode
{
    struct PokemonDefinition
    {
        std::string species;
        PokemonStatus status;
        int level;
        int hp_current;
        int experience;
        bool foreign;

        int dv_HP;
        int dv_ATK;
        int dv_DEF;
        int dv_SPC;
        int dv_SPD;

        int statusExperience_HP;
        int statusExperience_ATK;
        int statusExperience_DEF;
        int statusExperience_SPC;
        int statusExperience_SPD;

        std::string attack_1;
        int attack_1_pp;
        int attack_1_pp_current;

        std::string attack_2;
        int attack_2_pp;
        int attack_2_pp_current;

        std::string attack_3;
        int attack_3_pp;
        int attack_3_pp_current;

        std::string attack_4;
        int attack_4_pp;
        int attack_4_pp_current;
    };
}

#endif // POKEMONDEFITION_HPP
