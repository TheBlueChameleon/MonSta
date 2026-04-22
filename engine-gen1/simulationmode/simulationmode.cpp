#include "services/loggerservice.hpp"

#include "base/enginebase.hpp"

#include "setup/mechanicsdefinitionsetup.hpp"
#include "setup/teamdefinitionsetup.hpp"
#include "setup/typedefinitionsetup.hpp"

#include "registry.hpp"
#include "setup.hpp"
#include "simulationmode.hpp"

namespace SimulationMode
{
    void setupSimulationMode(const IMatchDefinition& matchDefinition)
    {
        EngineBase::ErrorBuffer eb;
        LoggerService::debug("setup for simulation mode started...");

        loadAndRegisterMechanicsDefinition(matchDefinition.mechanics, eb);
        loadAndRegisterTeamDefinition(matchDefinition.player1Team, JHND_PLAYER1_TEAMDEFINITION, player1TeamDefinition, eb);
        loadAndRegisterTeamDefinition(matchDefinition.player2Team, JHND_PLAYER2_TEAMDEFINITION, player2TeamDefinition, eb);
        loadAndRegisterTypesDefinition(matchDefinition.typeDefs, eb);
        loadAndRegisterPokemon(matchDefinition.pkmnDefs, eb);

        if (!eb.isClean())
        {
            throw EngineError(eb.compileErrorMessage().data());
        }

        LoggerService::infoF("### team 1 ({})", player1TeamDefinition.name);
        for (const auto p : player1TeamDefinition.pokemon)
        {
            LoggerService::infoF("### - {}", p.species);
        }
        LoggerService::infoF("### team 2({})", player2TeamDefinition.name);
        for (const auto p : player2TeamDefinition.pokemon)
        {
            LoggerService::infoF("### - {}", p.species);
        }
        LoggerService::infoF("### Dragon moves are {}", getMoveCategoryName(typeChart.getMoveCategoryForType("Dragon")));
        LoggerService::infoF("### Dragonair is a {}", pokemonDatabase.getEntry("Dragonair").type.primary);

        LoggerService::debug("... done");
    }
}
