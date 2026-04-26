#include <algorithm>
#include <format>
#include <span>
#include <unordered_map>

#include <base/errorbuffer.hpp>

#include <services/csvservice.hpp>
#include <services/jsonservice.hpp>
#include <services/loggerservice.hpp>

#include "shared/schemavalidationconstants.hpp"
#include "shared/registry/registry.hpp"

#include "shared/defs/teamdefinition.hpp"

#include "setuperrorhandling.hpp"
#include "teamdefinitionsetup.hpp"

using namespace std::string_literals;
using namespace EngineBase;
using namespace Registry;
using namespace MetaDefinition;
using namespace SchemaValidation;

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

    static void reportViolation(const std::string violationDescription)
    {
        Registry::metaViolations.push_back(violationDescription);
        LoggerService::warn(violationDescription.data());
    }

    // ====================================================================== //
    // processors proper

    static void warnIllegalPokemonStatBased(
        const std::string_view statName,
        const std::string_view pokemonName,
        const int statValue,
        const int statCap,
        const std::filesystem::path& origin
    )
    {
        if (statValue > Registry::mechanicsDefinition.dvCap)
        {
            reportViolation(std::format(
                                "In '{}':\n"
                                "Detected Pokémon species '{}' with {} {}.\n"
                                "This is above the cap of {}.",
                                origin.c_str(),
                                pokemonName,
                                statName, statValue,
                                statCap
                            ));
        }
    }

    static void warnIllegalPokemon(
        const PokemonDefinition& pokemon,
        const std::filesystem::path& origin
    )
    {
        const size_t dvSum =
            pokemon.dv_ATK +
            pokemon.dv_DEF +
            pokemon.dv_SPC +
            pokemon.dv_SPC +
            pokemon.dv_HP;

        const size_t sxSum =
            pokemon.statusExperience_ATK +
            pokemon.statusExperience_DEF +
            pokemon.statusExperience_SPC +
            pokemon.statusExperience_SPD +
            pokemon.statusExperience_HP;

        warnIllegalPokemonStatBased("level", pokemon.species, pokemon.level, Registry::mechanicsDefinition.levelCap, origin);

        warnIllegalPokemonStatBased("HP DV", pokemon.species, pokemon.dv_HP, Registry::mechanicsDefinition.dvCap, origin);
        warnIllegalPokemonStatBased("ATK DV", pokemon.species, pokemon.dv_ATK, Registry::mechanicsDefinition.dvCap, origin);
        warnIllegalPokemonStatBased("DEF DV", pokemon.species, pokemon.dv_DEF, Registry::mechanicsDefinition.dvCap, origin);
        warnIllegalPokemonStatBased("SPC DV", pokemon.species, pokemon.dv_SPC, Registry::mechanicsDefinition.dvCap, origin);
        warnIllegalPokemonStatBased("SPC DV", pokemon.species, pokemon.dv_SPD, Registry::mechanicsDefinition.dvCap, origin);
        warnIllegalPokemonStatBased("DV sum", pokemon.species, dvSum, Registry::mechanicsDefinition.dvSumCap, origin);

        warnIllegalPokemonStatBased("HP StatExperience", pokemon.species,  pokemon.statusExperience_HP,  Registry::mechanicsDefinition.statExpCap, origin);
        warnIllegalPokemonStatBased("ATK StatExperience", pokemon.species, pokemon.statusExperience_ATK, Registry::mechanicsDefinition.statExpCap, origin);
        warnIllegalPokemonStatBased("DEF StatExperience", pokemon.species, pokemon.statusExperience_DEF, Registry::mechanicsDefinition.statExpCap, origin);
        warnIllegalPokemonStatBased("SPC StatExperience", pokemon.species, pokemon.statusExperience_SPC, Registry::mechanicsDefinition.statExpCap, origin);
        warnIllegalPokemonStatBased("SPC StatExperience", pokemon.species, pokemon.statusExperience_SPD, Registry::mechanicsDefinition.statExpCap, origin);
        warnIllegalPokemonStatBased("StatExperience sum", pokemon.species, sxSum, Registry::mechanicsDefinition.statExpSumCap, origin);
    }

    static PokemonDefinition processPokemon(
        const JsonService::JsonWrapper& pkmnDef,
        bool humanMode,
        const std::filesystem::path& origin
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

        warnIllegalPokemon(result, origin);
        return result;
    }

    static void processPokemonList(
        const JsonService::JsonWrapper& listJson,
        std::vector<PokemonDefinition>& pokemonList,
        bool humanMode,
        const std::filesystem::path& origin
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
        else if (listSize > Registry::mechanicsDefinition.teamSizeMax)
        {
            reportViolation(std::format(
                                "In '{}':\n"
                                "Detected an overlarge team of size {}.\n"
                                "This is above the cap of {}.",
                                origin.c_str(),
                                listSize, Registry::mechanicsDefinition.teamSizeMax
                            ));
        }

        for (size_t i = 0; i < listSize; ++i)
        {
            const auto itemHandle = listJson.getArrayItem(i);
            pokemonList.push_back(
                processPokemon(itemHandle, humanMode, origin)
            );
        }
    }

    static void processItem(
        const JsonService::JsonWrapper& itemJson,
        std::vector<std::string>& itemsList,
        const size_t index,
        ErrorBuffer& eb
    )
    {
        if (itemJson.isString())
        {
            itemsList.push_back(itemJson.getAsString().data());
        }
        else if (itemJson.isObject())
        {
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
                "Illegal syntax in definition of Item #"s + std::to_string(index)
            );
        }
    }

    static void processItemList(
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
            processItem(itemJson, itemsList, i, eb);
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

            std::string teamHandleName = jtag_base + teamDefinitionFile.c_str();
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
                teamJson.navigateTo(JKEY_POKEMON),
                team.pokemon,
                isHuman,
                teamDefinitionFile
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
