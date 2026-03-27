#include <string>
using namespace std::string_literals;

#include "schemaconstants.hpp"
#include "schemaconstantsbuilder.hpp"
using namespace JsonSchemaBuilderUtils;

using Json = nlohmann::json;

static const auto t_boolean = "\"boolean\"";
static const auto t_integer = "\"integer\"";
static const auto t_string  = "\"string\"";

// ========================================================================== //
// SHARED
// -------------------------------------------------------------------------- //
// logging

static const JsonSubSchemaBuilder makeLoggingSubSchema()
{
    auto logging = JsonSubSchemaBuilder(JKEY_LOGGING);

    logging.addProperty(JKEY_LOGGING_LOGFILE, t_string);

    logging.addProperty(JKEY_LOGGING_LOGLEVEL, t_integer)
    .addKeyValuePair("minimum", "0")
    .addKeyValuePair("maximum", "6");

    return logging;
}

// ========================================================================== //
// SIMULATION
// -------------------------------------------------------------------------- //
// simulator

static const JsonSubSchemaBuilder makeSimulatorSubSchema()
{
    auto simulator = JsonSubSchemaBuilder(JKEY_SIMULATOR)
                     .setRequired(
    {
        JKEY_SIMULATOR_ENGINE
    });

    simulator.addProperty(JKEY_SIMULATOR_ENGINE, t_string);

    simulator.addProperty(JKEY_SIMULATOR_INPUTDIRECTORY, t_string);

    simulator.addProperty(JKEY_SIMULATOR_OUTPUTDIRECTORY, t_string);

    simulator.addProperty(JKEY_SIMULATOR_REPETITIONS, t_integer)
    .addKeyValuePair("minimum", "1");

    simulator.addProperty(JKEY_SIMULATOR_MAXTURNS, t_integer)
    .addKeyValuePair("minimum", "1");

    simulator.addProperty(JKEY_SIMULATOR_THREADCOUNT, t_integer)
    .addKeyValuePair("minimum", "1");

    simulator.addProperty(JKEY_SIMULATOR_ARGS, t_string);

    return simulator;
}

// -------------------------------------------------------------------------- //
// match definition

static const JsonSubSchemaBuilder makeMatchDefinitionSubSchema()
{
    auto matchDefinition = JsonSubSchemaBuilder(JKEY_MATCHDEFINITION)
                           .setRequired(
    {
        JKEY_MATCHDEFINITION_PLAYER1TEAM,
        JKEY_MATCHDEFINITION_PLAYER1STRATETY,
        JKEY_MATCHDEFINITION_PLAYER2TEAM,
        JKEY_MATCHDEFINITION_PLAYER2STRATETY,
        JKEY_MATCHDEFINITION_PKMNDEFS,
        JKEY_MATCHDEFINITION_MOVEDEFS,
        JKEY_MATCHDEFINITION_TYPEDEFS,
        JKEY_MATCHDEFINITION_ITEMDEFS
    });

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1STRATETY, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2STRATETY, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1TEAM, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2TEAM, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_PKMNDEFS, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_MOVEDEFS, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_TYPEDEFS, t_string);

    matchDefinition.addProperty(JKEY_MATCHDEFINITION_ITEMDEFS, t_string);

    return matchDefinition;
}

// -------------------------------------------------------------------------- //
// FULL SCHEMA

static const JsonSchemaBuilder makeSimulationSchema()
{
    auto simulation = JsonSchemaBuilder()
                      .addReference(JKEY_LOGGING, "logging")
                      .addReference(JKEY_SIMULATOR, "simulator")
                      .addReference(JKEY_MATCHDEFINITION, "match definition")
                      .addSubSchema(makeLoggingSubSchema())
                      .addSubSchema(makeSimulatorSubSchema())
                      .addSubSchema(makeMatchDefinitionSubSchema())
                      .setRequired(
    {
        JKEY_SIMULATOR, JKEY_MATCHDEFINITION
    });

    return simulation;
}

const std::string SCHEMA_SIMULATION_STRING = makeSimulationSchema().build();
const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

// ========================================================================== //
// TEMPLATE
// -------------------------------------------------------------------------- //
// templates

static const JsonSubSchemaBuilder makeTemplateDefinitionSubSchema()
{
    auto result = JsonSubSchemaBuilder(JKEY_TEMPLATE)
                  .setRequired(
    {
        JKEY_TEMPLATE_ENGINE
    });

    result.addProperty(JKEY_TEMPLATE_ENGINE, t_string);

    result.addProperty(JKEY_TEMPLATE_OUTPUTDIRECTORY, t_string);

    result.addProperty(JKEY_TEMPLATE_WRITESCHEMAS, t_boolean);

    result.addProperty(JKEY_TEMPLATE_PLAYER1TEAM, t_string);

    result.addProperty(JKEY_TEMPLATE_PLAYER1STRATEGY, t_string);

    result.addProperty(JKEY_TEMPLATE_PLAYER2TEAM, t_string);

    result.addProperty(JKEY_TEMPLATE_PLAYER2STRATEGY, t_string);

    result.addProperty(JKEY_TEMPLATE_PKMNDEFS, t_string);

    result.addProperty(JKEY_TEMPLATE_MOVEDEFS, t_string);

    result.addProperty(JKEY_TEMPLATE_TYPEDEFS, t_string);

    result.addProperty(JKEY_TEMPLATE_ARGS, t_string);

    return result;
}

// -------------------------------------------------------------------------- //
// FULL SCHEMA

static const JsonSchemaBuilder makeTemplateSchema()
{
    auto result = JsonSchemaBuilder()
                  .addReference(JKEY_LOGGING, "logging")
                  .addReference(JKEY_TEMPLATE, "template")
                  .addSubSchema(makeLoggingSubSchema())
                  .addSubSchema(makeTemplateDefinitionSubSchema())
                  .setRequired(
    {
        JKEY_TEMPLATE
    });

    return result;
}

const std::string SCHEMA_TEMPLATE_STRING = makeTemplateSchema().build();
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);
