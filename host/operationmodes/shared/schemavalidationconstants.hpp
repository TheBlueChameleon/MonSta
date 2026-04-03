#ifndef SCHEMAVALIDATIONCONSTANTS_HPP
#define SCHEMAVALIDATIONCONSTANTS_HPP

static constexpr auto JTAG_BASE = ":storage:/host/";

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

static constexpr auto JTAG_SIMULATION = ":storage:/host/:validation:/simulation.json";

static constexpr auto JKEY_MATCHDEFINITION                 = "matchDefinition";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER1TEAM     = "player1Team";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER1STRATETY = "player1Strategy";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER2TEAM     = "player2Team";
static constexpr auto JKEY_MATCHDEFINITION_PLAYER2STRATETY = "player2Strategy";
static constexpr auto JKEY_MATCHDEFINITION_PKMNDEFS        = "pkmnDefs";
static constexpr auto JKEY_MATCHDEFINITION_MOVEDEFS        = "moveDefs";
static constexpr auto JKEY_MATCHDEFINITION_TYPEDEFS        = "typeDefs";
static constexpr auto JKEY_MATCHDEFINITION_ITEMDEFS        = "itemDefs";

static constexpr auto JKEY_TEMPLATES                 = "templates";
static constexpr auto JKEY_TEMPLATES_ENGINE          = "engine";
static constexpr auto JKEY_TEMPLATES_OUTPUTDIRECTORY = "outputDirectory";
static constexpr auto JKEY_TEMPLATES_WRITESCHEMAS    = "writeSchemas";
static constexpr auto JKEY_TEMPLATES_PLAYER1TEAM     = "player1Team";
static constexpr auto JKEY_TEMPLATES_PLAYER1STRATEGY = "player1Strategy";
static constexpr auto JKEY_TEMPLATES_PLAYER2TEAM     = "player2Team";
static constexpr auto JKEY_TEMPLATES_PLAYER2STRATEGY = "player2Strategy";
static constexpr auto JKEY_TEMPLATES_PKMNDEFS        = "pkmnDefs";
static constexpr auto JKEY_TEMPLATES_MOVEDEFS        = "moveDefs";
static constexpr auto JKEY_TEMPLATES_TYPEDEFS        = "typeDefs";
static constexpr auto JKEY_TEMPLATES_ITEMDEFS        = "itemDefs";
static constexpr auto JKEY_TEMPLATES_ARGS            = "args";

static constexpr auto JTAG_TEMPLATES = ":storage:/host/:validation:/templates.json";

namespace OperationModes
{
    void registerSchemaSimulation();
    void registerSchemaTemplate();
}
#endif // SCHEMACONSTANTS_HPP
