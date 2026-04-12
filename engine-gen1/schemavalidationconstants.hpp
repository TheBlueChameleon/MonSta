#ifndef SCHEMAVALIDATIONCONSTANTS_HPP
#define SCHEMAVALIDATIONCONSTANTS_HPP

#include <services/IJsonService.hpp>

#include "services/jsonservice.hpp"
#include "services/loggerservice.hpp"

namespace SchemaValidation
{
    extern const IJsonServiceTypes::JsonTag JTAG_BASE;
    extern const IJsonServiceTypes::JsonTag JTAG_TEAMDEFINITION;

    const auto JKEY_COMPUTER = "computer";
    const auto JKEY_HUMAN    = "human";
    const auto JKEY_POKEMON  = "pokemon";

    const auto JKEY_PLAYER_BADGES           = "badges";
    const auto JKEY_PLAYER_BADGES_BROCK     = "Brock";
    const auto JKEY_PLAYER_BADGES_MISTY     = "Misty";
    const auto JKEY_PLAYER_BADGES_SURGE     = "Surge";
    const auto JKEY_PLAYER_BADGES_ERIKA     = "Erika";
    const auto JKEY_PLAYER_BADGES_SABRINA   = "Sabrina";
    const auto JKEY_PLAYER_BADGES_KOGA      = "Koga";
    const auto JKEY_PLAYER_BADGES_BLAINE    = "Blaine";
    const auto JKEY_PLAYER_BADGES_GIOVANNI  = "Giovanni";

    const auto JKEY_PLAYER_STATUSMOVEDEBUFF = "statMoveDebuf";
    const auto JKEY_PLAYER_USEPP            = "usePP";

    void registerSchemaTeamDefinition();
}

#endif // SCHEMAVALIDATIONCONSTANTS_HPP
