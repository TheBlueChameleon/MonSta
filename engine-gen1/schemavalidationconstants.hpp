#ifndef SCHEMAVALIDATIONCONSTANTS_HPP
#define SCHEMAVALIDATIONCONSTANTS_HPP

#include <string>

#include <services/IJsonService.hpp>

#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

namespace SchemaValidation
{
    const auto filename_mechanicsDefinitionSchema = "mechanicsDefinitionSchema.json";
    const auto filename_teamDefinitionSchema      = "teamDefinitionSchema.json";

    extern const std::string jtag_mechanicsDefinition;
    extern const std::string jtag_teamDefinition;

    extern const IJsonServiceTypes::JsonTag JTAG_MECHANICSDEFINITION;
    extern const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION;

    const auto JKEY_COMPUTER  = "computer";
    const auto JKEY_HUMAN     = "human";
    const auto JKEY_POKEMON   = "pokemon";

    const auto JKEY_PLAYER_NAME             = "name";
    const auto JKEY_PLAYER_BADGEATK         = "badgeBoost_ATK";
    const auto JKEY_PLAYER_BADGEDEF         = "badgeBoost_DEF";
    const auto JKEY_PLAYER_BADGESPC         = "badgeBoost_SPC";
    const auto JKEY_PLAYER_BADGESPD         = "badgeBoost_SPD";
    const auto JKEY_PLAYER_STATUSMOVEDEBUFF = "statMoveDebuf";
    const auto JKEY_PLAYER_USEPP            = "usePP";
    const auto JKEY_PLAYER_EXPALL           = "ExpAll";
    const auto JKEY_PLAYER_OBEDIENCECAP     = "obedienceCap";

    const auto JKEY_POKEMON_SPECIES = "species";
    const auto JKEY_POKEMON_LEVEL   = "level";
    const auto JKEY_POKEMON_EXP     = "experience";
    const auto JKEY_POKEMON_FOREIGN = "foreign";
    const auto JKEY_POKEMON_STATUS  = "status";

    const auto JKEY_POKEMON_HPCURRENT  = "HP_current";

    const auto JKEY_POKEMON_DVHP  = "DV_HP";
    const auto JKEY_POKEMON_DVATK = "DV_ATK";
    const auto JKEY_POKEMON_DVDEF = "DV_DEF";
    const auto JKEY_POKEMON_DVSPC = "DV_SPC";
    const auto JKEY_POKEMON_DVSPD = "DV_SPD";

    const auto JKEY_POKEMON_STATEXPHP  = "StatusExperience_HP";
    const auto JKEY_POKEMON_STATEXPATK = "StatusExperience_ATK";
    const auto JKEY_POKEMON_STATEXPDEF = "StatusExperience_DEF";
    const auto JKEY_POKEMON_STATEXPSPC = "StatusExperience_SPC";
    const auto JKEY_POKEMON_STATEXPSPD = "StatusExperience_SPD";

    const auto JKEY_POKEMON_ATTACK1          = "attack_1";
    const auto JKEY_POKEMON_ATTACK1PP        = "attack_1_pp";
    const auto JKEY_POKEMON_ATTACK1PPCURRENT = "attack_1_pp_current";

    const auto JKEY_POKEMON_ATTACK2          = "attack_2";
    const auto JKEY_POKEMON_ATTACK2PP        = "attack_2_pp";
    const auto JKEY_POKEMON_ATTACK2PPCURRENT = "attack_2_pp_current";

    const auto JKEY_POKEMON_ATTACK3          = "attack_3";
    const auto JKEY_POKEMON_ATTACK3PP        = "attack_3_pp";
    const auto JKEY_POKEMON_ATTACK3PPCURRENT = "attack_3_pp_current";

    const auto JKEY_POKEMON_ATTACK4          = "attack_4";
    const auto JKEY_POKEMON_ATTACK4PP        = "attack_4_pp";
    const auto JKEY_POKEMON_ATTACK4PPCURRENT = "attack_4_pp_current";

    const auto JKEY_MECHANICS_LEVELCAP                  = "levelCap";
    const auto JKEY_MECHANICS_STATSMIN                  = "statsMin";
    const auto JKEY_MECHANICS_STATSMAX                  = "statsMax";
    const auto JKEY_MECHANICS_OBEDIENCE                 = "obedience";
    const auto JKEY_MECHANICS_GEN1MISS                  = "gen1miss";
    const auto JKEY_MECHANICS_BIDE_GLITCH               = "bideGlitch";
    const auto JKEY_MECHANICS_COUNTERGLITCH             = "counterGlitch";
    const auto JKEY_MECHANICS_CRITRATEGLITCH            = "critRateGlitch";
    const auto JKEY_MECHANICS_EXPUNDERFLOWGLITCH        = "experienceUnderflowGlitch";
    const auto JKEY_MECHANICS_HPRECOVERYGLITCH          = "hpRecoveryGlitch";
    const auto JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH     = "hyperbeamFreezeGlitch";
    const auto JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH      = "hyperbeamSleepGlitch";
    const auto JKEY_MECHANICS_INVULNERABILITYGLITCH     = "invulnerabilityGlitch";
    const auto JKEY_MECHANICS_JUMPKICKGLITCH            = "jumpKickGlitch";
    const auto JKEY_MECHANICS_MIMICLEVELUPGLITCH        = "mimicLevelUpGlitch";
    const auto JKEY_MECHANICS_STATMODGLITCH             = "statusModificationGlitch";
    const auto JKEY_MECHANICS_SUBSTITUTEHPDRAINGLITCH   = "substituteHpDrainGlitch";
    const auto JKEY_MECHANICS_SUBSTITUTESELFHURTGLITCH  = "substituteSelfHurtGlitch";
    const auto JKEY_MECHANICS_TOXICLEECHSEEDGLITCH      = "toxicLeechSeedGlitch";
    const auto JKEY_MECHANICS_TOXICRESTGLITCH           = "toxicRestGlitch";

    void registerMechanicsDefinition();
    void registerSchemaTeamDefinition();
}

#endif // SCHEMAVALIDATIONCONSTANTS_HPP
