#ifndef POKEMONDEFITION_HPP
#define POKEMONDEFITION_HPP

#include <string>

struct PokemonDefinition
{
    enum class Status { NORMAL, PARALYZED, POISONED, ASLEEP, BURNT, FROZEN, FAINTED };

    std::string species;
    Status status;
    int HP_current;
    int level;
    int experience;
    bool foreign;

    int DV_HP;
    int DV_ATK;
    int DV_DEF;
    int DV_SPC;
    int DV_SPD;

    int StatusExperience_HP;
    int StatusExperience_ATK;
    int StatusExperience_DEF;
    int StatusExperience_SPC;
    int StatusExperience_SPD;

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

#endif // POKEMONDEFITION_HPP
