#ifndef SCHEMAVALIDATIONCONSTANTS_HPP
#define SCHEMAVALIDATIONCONSTANTS_HPP

#include <string>

#include <services/IJsonService.hpp>

namespace OperationModes
{
    const auto filename_simulationDefinition = "simulationDefinition.json";
    const auto filename_templatesDefinition  = "templatesDefinition.json";

    extern const std::string jtag_base;
    extern const std::string jtag_simulation;
    extern const std::string jtag_templates;

    extern const IJsonServiceTypes::JsonTag JTAG_SIMULATION;
    extern const IJsonServiceTypes::JsonTag JTAG_TEMPLATES;

    static const auto JKEY_LOGGING          = "logging";
    static const auto JKEY_LOGGING_LOGFILE  = "logfile";
    static const auto JKEY_LOGGING_LOGLEVEL = "loglevel";

    static const auto JKEY_PATHS                 = "paths";
    static const auto JKEY_PATHS_INPUTDIRECTORY  = "inputDirectory";
    static const auto JKEY_PATHS_OUTPUTDIRECTORY = "outputDirectory";
    static const auto JKEY_PATHS_ENGINE          = "engine";

    static const auto JKEY_SIMULATOR                 = "simulator";
    static const auto JKEY_SIMULATOR_REPETITIONS     = "repetitions";
    static const auto JKEY_SIMULATOR_MAXTURNS        = "maxTurns";
    static const auto JKEY_SIMULATOR_THREADCOUNT     = "threadCount";

    static const auto JKEY_MATCHDEFINITION                 = "matchDefinition";
    static const auto JKEY_MATCHDEFINITION_MECHANICS       = "mechanics";
    static const auto JKEY_MATCHDEFINITION_PLAYER1TEAM     = "player1Team";
    static const auto JKEY_MATCHDEFINITION_PLAYER1STRATETY = "player1Strategy";
    static const auto JKEY_MATCHDEFINITION_PLAYER2TEAM     = "player2Team";
    static const auto JKEY_MATCHDEFINITION_PLAYER2STRATETY = "player2Strategy";
    static const auto JKEY_MATCHDEFINITION_PKMNDEFS        = "pkmnDefs";
    static const auto JKEY_MATCHDEFINITION_MOVEDEFS        = "moveDefs";
    static const auto JKEY_MATCHDEFINITION_TYPEDEFS        = "typeDefs";
    static const auto JKEY_MATCHDEFINITION_ITEMDEFS        = "itemDefs";
    static const auto JKEY_MATCHDEFINITION_ARGS            = "args";

    static const auto JKEY_TEMPLATES                 = "templates";
    static const auto JKEY_TEMPLATES_MECHANICS       = "mechanics";
    static const auto JKEY_TEMPLATES_PLAYER1TEAM     = "player1Team";
    static const auto JKEY_TEMPLATES_PLAYER1STRATEGY = "player1Strategy";
    static const auto JKEY_TEMPLATES_PLAYER2TEAM     = "player2Team";
    static const auto JKEY_TEMPLATES_PLAYER2STRATEGY = "player2Strategy";
    static const auto JKEY_TEMPLATES_PKMNDEFS        = "pkmnDefs";
    static const auto JKEY_TEMPLATES_MOVEDEFS        = "moveDefs";
    static const auto JKEY_TEMPLATES_TYPEDEFS        = "typeDefs";
    static const auto JKEY_TEMPLATES_ITEMDEFS        = "itemDefs";
    static const auto JKEY_TEMPLATES_WRITESCHEMAS    = "writeSchemas";
    static const auto JKEY_TEMPLATES_ALLOWEDVALUES   = "writeAllowedValues";
    static const auto JKEY_TEMPLATES_ARGS            = "args";

    void registerSchemaSimulation();
    void registerSchemaTemplate();
}
#endif // SCHEMACONSTANTS_HPP
