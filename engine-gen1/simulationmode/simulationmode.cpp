#include <string>

#include "services/loggerservice.hpp"
#include "services/jsonservice.hpp"

#include "base/enginebase.hpp"

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

#include "registry.hpp"
#include "simulationmode.hpp"
#include "teamdefinition.hpp"

using namespace EngineBase;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    static bool getFlag(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer
    )
    {
        const auto targetHandle = JsonService::navigateTo(handle, jsonPointer);
        return JsonService::getAsBool(targetHandle);
    }

    static int getInt(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer
    )
    {
        const auto targetHandle = JsonService::navigateTo(handle, jsonPointer);
        return JsonService::getAsInteger(targetHandle);
    }

    static std::string_view getString(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer
    )
    {
        const auto targetHandle = JsonService::navigateTo(handle, jsonPointer);
        return JsonService::getAsString(targetHandle);
    }

    static std::string_view getPlayerBaseObjectName(const IJsonServiceTypes::JsonHandle handle)
    {
        // *INDENT-OFF*
        if      (JsonService::contains(handle, JKEY_HUMAN))    { return JKEY_HUMAN; }
        else if (JsonService::contains(handle, JKEY_COMPUTER)) { return JKEY_COMPUTER; }
        else {
            throw EngineError(
                ApiStatusCode::JSON_ERROR,
                "team definition neither contains '"s + JKEY_HUMAN + "' tag "
                "nor '" + JKEY_COMPUTER + "' tag");
        }
        // *INDENT-ON*
    }

    static std::string getPlayerObjectJsonPointer(const IJsonServiceTypes::JsonHandle handle, std::string_view element)
    {
        std::string result = "/";
        result += getPlayerBaseObjectName(handle).data();
        result += "/";
        result += element;

        return result;
    }

    void loadAndRegisterMechanicsDefinition(
        const std::filesystem::path& mechanicsDefinitionFile,
        ErrorBuffer& eb
    )
    {
        try
        {
            LoggerService::traceF("  ... loading mechanics definition from '{}'", mechanicsDefinitionFile.c_str());

            std::string mechanicsHandleName = Globals::jtag_base + mechanicsDefinitionFile.c_str();
            JHND_MECHANICSDEFINITION = JsonService::readValidatePatchAndAdd(
                                           IJsonServiceTypes::JsonTag(mechanicsHandleName.data()),
                                           mechanicsDefinitionFile,
                                           JTAG_MECHANICSDEFINITION
                                       );

            mechanicsDefinition.levelCap    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_LEVELCAP);
            mechanicsDefinition.statsMin    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_STATSMIN);
            mechanicsDefinition.statsMax    = getInt(JHND_MECHANICSDEFINITION,  JKEY_MECHANICS_STATSMAX);
            mechanicsDefinition.obedience   = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_OBEDIENCE);
            mechanicsDefinition.gen1miss    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_GEN1MISS);

            mechanicsDefinition.bideGlitch                  = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_BIDE_GLITCH);
            mechanicsDefinition.counterGlitch               = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_COUNTERGLITCH);
            mechanicsDefinition.critRateGlitch              = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_CRITRATEGLITCH);
            mechanicsDefinition.experienceUnderflowGlitch   = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_EXPUNDERFLOWGLITCH);
            mechanicsDefinition.hpRecoveryGlitch            = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HPRECOVERYGLITCH);
            mechanicsDefinition.hyperbeamFreezeGlitch       = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HYPERBEAMFREEZEGLITCH);
            mechanicsDefinition.hyperbeamSleepGlitch        = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_HYPERBEAMSLEEPGLITCH);
            mechanicsDefinition.invulnerabilityGlitch       = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_INVULNERABILITYGLITCH);
            mechanicsDefinition.jumpKickGlitch              = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_JUMPKICKGLITCH);
            mechanicsDefinition.mimicLevelUpGlitch          = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_MIMICLEVELUPGLITCH);
            mechanicsDefinition.statusModificationGlitch    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_STATMODGLITCH);
            mechanicsDefinition.substituteHpDrainGlitch     = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_SUBSTITUTEHPDRAINGLITCH);
            mechanicsDefinition.substituteSelfHurtGlitch    = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_SUBSTITUTESELFHURTGLITCH);
            mechanicsDefinition.toxicLeechSeedGlitch        = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_TOXICLEECHSEEDGLITCH);
            mechanicsDefinition.toxicRestGlitch             = getFlag(JHND_MECHANICSDEFINITION, JKEY_MECHANICS_TOXICRESTGLITCH);
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }

    void loadAndRegisterTeamDefinition(
        const std::filesystem::path& teamDefinitionFile,
        IJsonServiceTypes::JsonHandle& teamHandle,
        TeamDefinition& team,
        ErrorBuffer& eb
    )
    {
        try
        {
            LoggerService::traceF("  ... loading team definition from '{}'", teamDefinitionFile.c_str());

            std::string teamHandleName = Globals::jtag_base + teamDefinitionFile.c_str();
            teamHandle = JsonService::readValidatePatchAndAdd(
                             IJsonServiceTypes::JsonTag(teamHandleName.data()),
                             teamDefinitionFile,
                             JTAG_TEAMDEFINITION
                         );

            team.name           = getString(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_NAME).data());
            team.expAll         = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_EXPALL).data());
            team.badgeBoost_ATK = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_BADGEATK).data());
            team.badgeBoost_DEF = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_BADGEDEF).data());
            team.badgeBoost_SPC = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_BADGESPC).data());
            team.badgeBoost_SPD = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_BADGESPD).data());
            team.statMoveDebuf  = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_STATUSMOVEDEBUFF).data());
            team.usePP          = getFlag(teamHandle, getPlayerObjectJsonPointer(teamHandle, JKEY_PLAYER_BADGEATK).data());
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }

    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        ErrorBuffer eb;
        LoggerService::debug("setup for simulation mode started...");

        loadAndRegisterMechanicsDefinition(matchDefinition.mechanics, eb);
        loadAndRegisterTeamDefinition(matchDefinition.player1Team, JHND_PLAYER1_TEAMDEFINITION, player1TeamDefinition, eb);
        loadAndRegisterTeamDefinition(matchDefinition.player2Team, JHND_PLAYER2_TEAMDEFINITION, player2TeamDefinition, eb);

        if (!eb.isClean())
        {
            throw EngineError(eb.compileErrorMessage().data());
        }

        LoggerService::debug("... done");
    }
}
