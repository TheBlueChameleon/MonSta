#ifndef SCHEMACONSTANTS_HPP
#define SCHEMACONSTANTS_HPP

static constexpr auto JKEY_LOGGING          = "logging";
static constexpr auto JKEY_LOGGING_LOGFILE  = "logfile";
static constexpr auto JKEY_LOGGING_LOGLEVEL = "loglevel";

static constexpr auto JKEY_SIMULATOR                 = "simulator";
static constexpr auto JKEY_SIMULATOR_ENGINE          = "engine";
static constexpr auto JKEY_SIMULATOR_INPUTDIRECTORY  = "inputDirectory";
static constexpr auto JKEY_SIMULATOR_OUTPUTDIRECTORY = "outputDirectory";
static constexpr auto JKEY_SIMULATOR_REPETITIONS     = "repetitions";
static constexpr auto JKEY_SIMULATOR_MAXTURNS        = "maxTurns";
static constexpr auto JKEY_SIMULATOR_THREADCOUNT     = "threadCount";
static constexpr auto JKEY_SIMULATOR_ARGS            = "args";

static constexpr auto JTAG_SIMULATION = ":storage:/host/simulation.json";

static constexpr auto JKEY_MATCHDEFINITION                 = "matchDefinition";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER1TEAM     = "player1Team";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER1STRATETY = "player1Strategy";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER2TEAM     = "player2Team";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER2STRATETY = "player2Strategy";
static constexpr auto JKEY_MATCHDEFINITION_PKMNDEFS        = "pkmnDefs";
static constexpr auto JKEY_MATCHDEFINITION_MOVEDEFS        = "moveDefs";
static constexpr auto JKEY_MATCHDEFINITION_TYPEDEFS        = "typeDefs";
static constexpr auto JKEY_MATCHDEFINITION_ITEMDEFS        = "itemDefs";

static constexpr auto JKEY_TEMPLATE                 = "template";
static constexpr auto JKEY_TEMPLATE_ENGINE          = "engine";
static constexpr auto JKEY_TEMPLATE_OUTPUTDIRECTORY = "outputDirectory";
static constexpr auto JKEY_TEMPLATE_WRITESCHEMAS    = "writeSchemas";
static constexpr auto JKEY_TEMPLATE_PLAYER1TEAM     = "player1Team";
static constexpr auto JKEY_TEMPLATE_PLAYER1STRATEGY = "player1Strategy";
static constexpr auto JKEY_TEMPLATE_PLAYER2TEAM     = "player2Team";
static constexpr auto JKEY_TEMPLATE_PLAYER2STRATEGY = "player2Strategy";
static constexpr auto JKEY_TEMPLATE_PKMNDEFS        = "pkmnDefs";
static constexpr auto JKEY_TEMPLATE_MOVEDEFS        = "moveDefs";
static constexpr auto JKEY_TEMPLATE_TYPEDEFS        = "typeDefs";
static constexpr auto JKEY_TEMPLATE_ITEMDEFS        = "itemDefs";
static constexpr auto JKEY_TEMPLATE_ARGS            = "args";

static constexpr auto JTAG_TEMPLATE = ":storage:/host/template.json";

namespace RunDefinitionUtils
{
    void registerSchemaSimulation();
    void registerSchemaTemplate();
}
#endif // SCHEMACONSTANTS_HPP
