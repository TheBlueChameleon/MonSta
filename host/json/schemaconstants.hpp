#ifndef SCHEMACONSTANTS_HPP
#define SCHEMACONSTANTS_HPP

#include <string>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

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

static constexpr auto JKEY_MATCHDEFINITION = "matchDefinition";

extern const std::string SCHEMA_SIMULATION_STRING;
extern const nlohmann::json SCHEMA_SIMULATION;

extern const std::string SCHEMA_TEMPLATE_STRING;
extern const nlohmann::json SCHEMA_TEMPLATE;

#endif // SCHEMACONSTANTS_HPP
