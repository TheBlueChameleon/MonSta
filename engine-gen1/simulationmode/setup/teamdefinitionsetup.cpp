#include <algorithm>
#include <span>
#include <sstream>
#include <unordered_map>

#include <base/enginebase.hpp>

#include <services/csvservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "globals.hpp"
#include "schemavalidationconstants.hpp"

#include "simulationmode/defs/teamdefinition.hpp"
// #include "simulationmode/defs/typeinfo.hpp"
#include "simulationmode/registry.hpp"


#include "teamdefinitionsetup.hpp"

using namespace EngineBase;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    // ====================================================================== //
    // helpers

    [[noreturn]] static void abort(
        const std::filesystem::path& origin,
        const std::string_view message
    )
    {
        throw EngineError(
            ApiStatusCode::INVALID_USER_INPUT,
            "In team definition file '"s + origin.c_str() + "' " + message.data()
        );
    }

    static bool getHumanStatus(
        const std::filesystem::path& origin,
        const JsonService::JsonWrapper json
    )
    {
        // *INDENT-OFF*
        if      (json.contains(JKEY_HUMAN))    { return true;  }
        else if (json.contains(JKEY_COMPUTER)) { return false; }
        else {
            abort(
                origin,
                "team definition neither contains '"s + JKEY_HUMAN + "' tag "
                "nor '" + JKEY_COMPUTER + "' tag"
            );
        }
        // *INDENT-ON*
    }

    static const char* const getPlayerBaseObjectName(const bool isHuman)
    {
        // *INDENT-OFF*
        if (isHuman) { return JKEY_HUMAN;    }
        else         { return JKEY_COMPUTER; }
        // *INDENT-ON*
    }

    static std::string getPlayerObjectJsonPointer(const bool isHuman, std::string_view element)
    {
        std::ostringstream result;
        result << "/" << getPlayerBaseObjectName(isHuman);
        result << "/" << element;
        return result.str();
    }

    // ====================================================================== //
    // loaders and processors

    static PokemonDefinition processPokemon(
        const JsonService::JsonWrapper& pkmnDef,
        bool humanMode
    )
    {
        PokemonDefinition result;

        result.species      =                          pkmnDef.navigateTo(JKEY_POKEMON_SPECIES).getAsString();
        result.status       = getPokemonStatusFromName(pkmnDef.navigateTo(JKEY_POKEMON_STATUS).getAsString());
        result.level        =                          pkmnDef.navigateTo(JKEY_POKEMON_LEVEL).getAsInteger();
        result.hp_current   =                          pkmnDef.navigateTo(JKEY_POKEMON_HPCURRENT).getAsInteger();
        result.experience   =                          pkmnDef.navigateTo(JKEY_POKEMON_EXP).getAsInteger();
        result.foreign      =                          pkmnDef.navigateTo(JKEY_POKEMON_FOREIGN).getAsBool();

        result.dv_HP        = pkmnDef.navigateTo(JKEY_POKEMON_DVHP). getAsInteger();
        result.dv_ATK       = pkmnDef.navigateTo(JKEY_POKEMON_DVATK).getAsInteger();
        result.dv_DEF       = pkmnDef.navigateTo(JKEY_POKEMON_DVDEF).getAsInteger();
        result.dv_SPC       = pkmnDef.navigateTo(JKEY_POKEMON_DVSPC).getAsInteger();
        result.dv_SPD       = pkmnDef.navigateTo(JKEY_POKEMON_DVSPD).getAsInteger();

        // *INDENT-OFF*
        if (result.dv_HP  == -1) { result.dv_HP  = (humanMode ? 15 : 8); }
        if (result.dv_ATK == -1) { result.dv_ATK = (humanMode ? 15 : 9); }      // sic: ATK is higher than other stats in NPC players
        if (result.dv_DEF == -1) { result.dv_DEF = (humanMode ? 15 : 8); }
        if (result.dv_SPC == -1) { result.dv_SPC = (humanMode ? 15 : 8); }
        if (result.dv_SPD == -1) { result.dv_SPD = (humanMode ? 15 : 8); }
        // *INDENT-ON*

        result.statusExperience_HP  = pkmnDef.navigateTo(JKEY_POKEMON_STATEXPHP).getAsInteger();
        result.statusExperience_ATK = pkmnDef.navigateTo(JKEY_POKEMON_STATEXPATK).getAsInteger();
        result.statusExperience_DEF = pkmnDef.navigateTo(JKEY_POKEMON_STATEXPDEF).getAsInteger();
        result.statusExperience_SPC = pkmnDef.navigateTo(JKEY_POKEMON_STATEXPSPC).getAsInteger();
        result.statusExperience_SPD = pkmnDef.navigateTo(JKEY_POKEMON_STATEXPSPD).getAsInteger();

        result.attack_1             = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1).getAsString();
        result.attack_1_pp          = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PP).getAsInteger();
        result.attack_1_pp_current  = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PPCURRENT).getAsInteger();

        result.attack_2             = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1).getAsString();
        result.attack_2_pp          = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PP).getAsInteger();
        result.attack_2_pp_current  = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PPCURRENT).getAsInteger();

        result.attack_3             = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1).getAsString();
        result.attack_3_pp          = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PP).getAsInteger();
        result.attack_3_pp_current  = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PPCURRENT).getAsInteger();

        result.attack_4             = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1).getAsString();
        result.attack_4_pp          = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PP).getAsInteger();
        result.attack_4_pp_current  = pkmnDef.navigateTo(JKEY_POKEMON_ATTACK1PPCURRENT).getAsInteger();

        return result;
    }

    static void processPokemonList(
        const std::filesystem::path& origin,
        const JsonService::JsonWrapper& listJson,
        bool humanMode,
        std::vector<PokemonDefinition>& pokemonList
    )
    {
        if (!listJson.isArray())
        {
            abort(origin, "The object under '"s + JKEY_POKEMON + "' is not a list");
        }

        const size_t listSize = listJson.getArraySize();
        if (listSize == 0)
        {
            abort(origin, "The object under '"s + JKEY_POKEMON + "' is empty");
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
            const auto itemHandle = listJson.getArrayItem(i);
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
            JsonService::JsonWrapper teamJson = JsonService::JsonWrapper(teamHandle);

            const bool isHuman = getHumanStatus(teamDefinitionFile, teamJson);

            team.name           = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_NAME)).getAsString().data();
            team.expAll         = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_EXPALL)).getAsBool();
            team.badgeBoost_ATK = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEATK)).getAsBool();
            team.badgeBoost_DEF = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEDEF)).getAsBool();
            team.badgeBoost_SPC = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGESPC)).getAsBool();
            team.badgeBoost_SPD = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGESPD)).getAsBool();
            team.statMoveDebuf  = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_STATUSMOVEDEBUFF)).getAsBool();
            team.usePP          = teamJson.navigateTo(getPlayerObjectJsonPointer(isHuman, JKEY_PLAYER_BADGEATK)).getAsBool();

            processPokemonList(
                teamDefinitionFile,
                teamJson.navigateTo(JKEY_POKEMON),
                isHuman,
                team.pokemon
            );
        }
        catch (const EngineError& e)
        {
            eb.append(e);
        }
    }
} // namespace SimulationMode
