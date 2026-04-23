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
#include "simulationmode/registry.hpp"

#include "setuperrorhandling.hpp"
#include "teamdefinitionsetup.hpp"

using namespace EngineBase;
using namespace SchemaValidation;
using namespace std::string_literals;

namespace SimulationMode
{
    // ====================================================================== //
    // helpers

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
                "team definition neither contains '"s + JKEY_HUMAN + "' tag "
                "nor '" + JKEY_COMPUTER + "' tag"
            );
        }
        // *INDENT-ON*
    }

    // ====================================================================== //
    // processors proper

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
            abort("The object under '"s + JKEY_POKEMON + "' is not a list", ApiStatusCode::ILLEGAL_CLIENT_STATE);
        }

        const size_t listSize = listJson.getArraySize();
        if (listSize == 0)
        {
            abort("The object under '"s + JKEY_POKEMON + "' is empty", ApiStatusCode::ILLEGAL_CLIENT_STATE);
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

    void processItem(
        const JsonService::JsonWrapper& itemJson,
        const size_t index,
        std::vector<std::string>& itemsList,
        ErrorBuffer& eb
    )
    {
        if (itemJson.isString())
        {
            itemsList.push_back(itemJson.getAsString().data());
        }
        else if (itemJson.isObject())
        {
            // TODO: eb.append Illegal status? Caught by Schema anyway...
            const std::string_view name     = itemJson.navigateTo(JKEY_PLAYER_ITEMS_NAME).getAsString();
            const size_t           quantity = itemJson.navigateTo(JKEY_PLAYER_ITEMS_QUANTITY).getAsInteger();
            for (size_t i = 0; i < quantity; ++i)
            {
                itemsList.push_back(name.data());
            }
        }
        else
        {
            eb.append(
                ApiStatusCode::ILLEGAL_CLIENT_STATE,
                "Item #"s + std::to_string(index) + " is of illegal type"
            );
        }
    }

    void processItemList(
        const JsonService::JsonWrapper& listJson,
        std::vector<std::string>& itemsList,
        ErrorBuffer& eb
    )
    {
        if (!listJson.isArray())
        {
            abort("The object under '"s + JKEY_PLAYER_ITEMS + "' is not a list", ApiStatusCode::ILLEGAL_CLIENT_STATE);
        }

        const size_t listSize = listJson.getArraySize();
        for (size_t i = 0; i < listSize; ++i)
        {
            const auto itemJson = listJson.getArrayItem(i);
            processItem(itemJson, i, itemsList, eb);
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
            JsonService::JsonWrapper playerJson = isHuman ?
                                                  teamJson.navigateTo(JKEY_HUMAN) :
                                                  teamJson.navigateTo(JKEY_COMPUTER);

            team.name           = playerJson.navigateTo(JKEY_PLAYER_NAME).getAsString().data();
            team.expAll         = playerJson.navigateTo(JKEY_PLAYER_EXPALL).getAsBool();
            team.badgeBoost_ATK = playerJson.navigateTo(JKEY_PLAYER_BADGEATK).getAsBool();
            team.badgeBoost_DEF = playerJson.navigateTo(JKEY_PLAYER_BADGEDEF).getAsBool();
            team.badgeBoost_SPC = playerJson.navigateTo(JKEY_PLAYER_BADGESPC).getAsBool();
            team.badgeBoost_SPD = playerJson.navigateTo(JKEY_PLAYER_BADGESPD).getAsBool();
            team.statMoveDebuf  = playerJson.navigateTo(JKEY_PLAYER_STATUSMOVEDEBUFF).getAsBool();
            team.usePP          = playerJson.navigateTo(JKEY_PLAYER_BADGEATK).getAsBool();

            processPokemonList(
                teamDefinitionFile,
                teamJson.navigateTo(JKEY_POKEMON),
                isHuman,
                team.pokemon
            );

            if (playerJson.contains(JKEY_PLAYER_ITEMS))
            {
                processItemList(
                    playerJson.navigateTo(JKEY_PLAYER_ITEMS),
                    team.items,
                    eb
                );
            }
        }
        catch (const EngineError& e)
        {
            report(eb, e.what(), teamDefinitionFile);
        }
    }
} // namespace SimulationMode
