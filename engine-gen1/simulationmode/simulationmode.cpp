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

    static bool getHumanStatus(const IJsonServiceTypes::JsonHandle handle)
    {
        // *INDENT-OFF*
        if      (JsonService::contains(handle, JKEY_HUMAN))    { return true; }
        else if (JsonService::contains(handle, JKEY_COMPUTER)) { return false; }
        else {
            throw EngineError(
                "team definition neither contains '"s + JKEY_HUMAN + "' tag "
                "nor '" + JKEY_COMPUTER + "' tag");
        }
        // *INDENT-ON*
    }

    static const char* const getPlayerBaseObjectName(const bool isHuman)
    {
        // *INDENT-OFF*
        if (isHuman) { return JKEY_HUMAN; }
        else         { return JKEY_COMPUTER; }
        // *INDENT-ON*
    }

    static std::string getPlayerObjectJsonPointer(const bool isHuman, std::string_view element)
    {
        std::string result = "/";
        result += getPlayerBaseObjectName(isHuman);
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

    PokemonDefinition processPokemon(
        const IJsonServiceTypes::JsonHandle pokemonHandle,
        bool humanMode
    )
    {
        PokemonDefinition result;

        result.species      = getString(pokemonHandle, JKEY_POKEMON_SPECIES);
        result.status       = getStatusFromName(getString(pokemonHandle, JKEY_POKEMON_STATUS));
        result.level        = getInt(pokemonHandle, JKEY_POKEMON_LEVEL);
        result.hp_current   = getInt(pokemonHandle, JKEY_POKEMON_HPCURRENT);
        result.experience   = getInt(pokemonHandle, JKEY_POKEMON_EXP);
        result.foreign      = getFlag(pokemonHandle, JKEY_POKEMON_FOREIGN);

        result.dv_HP        = getInt(pokemonHandle, JKEY_POKEMON_DVHP);
        result.dv_ATK       = getInt(pokemonHandle, JKEY_POKEMON_DVATK);
        result.dv_DEF       = getInt(pokemonHandle, JKEY_POKEMON_DVDEF);
        result.dv_SPC       = getInt(pokemonHandle, JKEY_POKEMON_DVSPC);
        result.dv_SPD       = getInt(pokemonHandle, JKEY_POKEMON_DVSPD);

        // *INDENT-OFF*
        if (result.dv_HP  == -1) { result.dv_HP  = (humanMode ? 15 : 8); }
        if (result.dv_ATK == -1) { result.dv_ATK = (humanMode ? 15 : 9); }
        if (result.dv_DEF == -1) { result.dv_DEF = (humanMode ? 15 : 8); }
        if (result.dv_SPC == -1) { result.dv_SPC = (humanMode ? 15 : 8); }
        if (result.dv_SPD == -1) { result.dv_SPD = (humanMode ? 15 : 8); }
        // *INDENT-ON*

        result.statusExperience_HP  = getInt(pokemonHandle, JKEY_POKEMON_STATEXPHP);
        result.statusExperience_ATK = getInt(pokemonHandle, JKEY_POKEMON_STATEXPATK);
        result.statusExperience_DEF = getInt(pokemonHandle, JKEY_POKEMON_STATEXPDEF);
        result.statusExperience_SPC = getInt(pokemonHandle, JKEY_POKEMON_STATEXPSPC);
        result.statusExperience_SPD = getInt(pokemonHandle, JKEY_POKEMON_STATEXPSPD);

        result.attack_1             = getString(pokemonHandle, JKEY_POKEMON_ATTACK1);
        result.attack_1_pp          = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PP);
        result.attack_1_pp_current  = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PPCURRENT);

        result.attack_2             = getString(pokemonHandle, JKEY_POKEMON_ATTACK1);
        result.attack_2_pp          = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PP);
        result.attack_2_pp_current  = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PPCURRENT);

        result.attack_3             = getString(pokemonHandle, JKEY_POKEMON_ATTACK1);
        result.attack_3_pp          = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PP);
        result.attack_3_pp_current  = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PPCURRENT);

        result.attack_4             = getString(pokemonHandle, JKEY_POKEMON_ATTACK1);
        result.attack_4_pp          = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PP);
        result.attack_4_pp_current  = getInt(pokemonHandle, JKEY_POKEMON_ATTACK1PPCURRENT);

        return result;
    }

    void processPokemonList(
        const std::filesystem::path& origin,
        const IJsonServiceTypes::JsonHandle listHandle,
        bool humanMode,
        std::vector<PokemonDefinition>& pokemonList
    )
    {
        if (!JsonService::isArray(listHandle))
        {
            throw EngineError("The object under '"s + JKEY_POKEMON + "' is not a list");
        }

        const size_t listSize = JsonService::getArraySize(listHandle);
        if (listSize == 0)
        {
            throw EngineError("The object under '"s + JKEY_POKEMON + "' is empty");
        }
        else if (listSize > 6)
        {
            LoggerService::warnF(
                "Detected an overlarge team (size {}) in {}",
                listSize, origin.c_str()
            );
        }

        for (size_t i = 0; i < listSize; ++i)
        {
            const auto itemHandle = JsonService::getArrayItem(listHandle, i);
            pokemonList.push_back(processPokemon(itemHandle, humanMode));
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

            const bool isHuman = getHumanStatus(teamHandle);

            team.name           = getString(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_NAME).data());
            team.expAll         = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_EXPALL).data());
            team.badgeBoost_ATK = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEATK).data());
            team.badgeBoost_DEF = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEDEF).data());
            team.badgeBoost_SPC = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGESPC).data());
            team.badgeBoost_SPD = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGESPD).data());
            team.statMoveDebuf  = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_STATUSMOVEDEBUFF).data());
            team.usePP          = getFlag(teamHandle, getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEATK).data());

            processPokemonList(
                teamDefinitionFile,
                JsonService::navigateTo(teamHandle, JKEY_POKEMON),
                isHuman,
                team.pokemon
            );
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

        LoggerService::infoF("team 1 ({})", player1TeamDefinition.name);
        for (const auto p : player1TeamDefinition.pokemon)
        {
            LoggerService::infoF("- {}", p.species);
        }
        LoggerService::infoF("team 2 ({})", player2TeamDefinition.name);
        for (const auto p : player2TeamDefinition.pokemon)
        {
            LoggerService::infoF("- {}", p.species);
        }

        LoggerService::debug("... done");
    }
}
