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

    const auto JKEY_PLAYER_BADGES           = "badges";
    const auto JKEY_PLAYER_STATUSMOVEDEBUFF = "statMoveDebuf";
    const auto JKEY_PLAYER_USEPP            = "usePP";

    void registerTeamDefinition();
}

#endif // SCHEMAVALIDATIONCONSTANTS_HPP
