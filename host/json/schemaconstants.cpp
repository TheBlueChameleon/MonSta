#include <string>
using namespace std::string_literals;

#include "schemaconstants.hpp"
#include "schemaconstantsbuilder.hpp"
using namespace JsonSchemaBuilderUtils;

using Json = nlohmann::json;

const std::string t_string = quoted("string");
const std::string t_integer = quoted("integer");

// ========================================================================== //
// SHARED
// -------------------------------------------------------------------------- //
// logging

auto logging = JsonSubSchemaBuilder(JKEY_LOGGING);
auto& logfile = logging.addProperty(JKEY_LOGGING_LOGFILE).addKeyValuePair("type", t_string);
auto& loglevel = logging.addProperty(JKEY_LOGGING_LOGLEVEL)
                 .addKeyValuePair("type", t_integer)
                 .addKeyValuePair("minimum", "0")
                 .addKeyValuePair("maximum", "6");

// ========================================================================== //
// SIMULATION
// -------------------------------------------------------------------------- //
// simulator

auto simulator = JsonSubSchemaBuilder(JKEY_SIMULATOR)
                 .setRequired(
{
    JKEY_SIMULATOR_ENGINE
});
auto& engine = simulator.addProperty(JKEY_SIMULATOR_ENGINE)
               .addKeyValuePair("type", t_string);
auto& outputDirectory = simulator.addProperty(JKEY_SIMULATOR_INPUTDIRECTORY)
                        .addKeyValuePair("type", t_string);
auto& inputDirectory = simulator.addProperty(JKEY_SIMULATOR_OUTPUTDIRECTORY)
                       .addKeyValuePair("type", t_string);
auto& repetitions = simulator.addProperty(JKEY_SIMULATOR_REPETITIONS)
                    .addKeyValuePair("type", t_integer)
                    .addKeyValuePair("minimum", "1");
auto& maxTurns = simulator.addProperty(JKEY_SIMULATOR_MAXTURNS)
                 .addKeyValuePair("type", t_integer)
                 .addKeyValuePair("minimum", "1");
auto& threadCount = simulator.addProperty(JKEY_SIMULATOR_THREADCOUNT)
                    .addKeyValuePair("type", t_integer)
                    .addKeyValuePair("minimum", "1");
auto& args = simulator.addProperty(JKEY_SIMULATOR_ARGS)
             .addKeyValuePair("type", t_string);

// -------------------------------------------------------------------------- //
// match definition

auto matchDefinition = JsonSubSchemaBuilder(JKEY_MATCHDEFINITION)
                       .setRequired(
{
    JKEY_MATCHDEFINITION_PLAYER1TEAM,
    JKEY_MATCHDEFINITION_PLAYER1STRATETY,
    JKEY_MATCHDEFINITION_PLAYER2TEAM,
    JKEY_MATCHDEFINITION_PLAYER2STRATETY,
    JKEY_MATCHDEFINITION_PKMNDEFS,
    JKEY_MATCHDEFINITION_MOVEDEFS,
    JKEY_MATCHDEFINITION_TYPEDEFS
});
auto& player1Strategy = matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1STRATETY)
                        .addKeyValuePair("type", t_string);
auto& player2Strategy = matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2STRATETY)
                        .addKeyValuePair("type", t_string);
auto& player1Team = matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1TEAM)
                    .addKeyValuePair("type", t_string);
auto& player2Team = matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2TEAM)
                    .addKeyValuePair("type", t_string);
auto& pkmnDefs = matchDefinition.addProperty(JKEY_MATCHDEFINITION_PKMNDEFS)
                 .addKeyValuePair("type", t_string);
auto& moveDefs = matchDefinition.addProperty(JKEY_MATCHDEFINITION_MOVEDEFS)
                 .addKeyValuePair("type", t_string);
auto& typeDefs = matchDefinition.addProperty(JKEY_MATCHDEFINITION_TYPEDEFS)
                 .addKeyValuePair("type", t_string);

// -------------------------------------------------------------------------- //
// FULL SCHEMA

auto simulation = JsonSchemaBuilder()
                  .addReference(JKEY_LOGGING, "logging")
                  .addReference(JKEY_SIMULATOR, "simulator")
                  .addReference(JKEY_MATCHDEFINITION, "match definition")
                  .addSubSchema(logging)
                  .addSubSchema(simulator)
                  .addSubSchema(matchDefinition)
                  .setRequired(
{
    JKEY_SIMULATOR, JKEY_MATCHDEFINITION
});
const std::string SCHEMA_SIMULATION_STRING = simulation.build();
const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

// ========================================================================== //
// TEMPLATE
// -------------------------------------------------------------------------- //
// templates

auto templateS = JsonSubSchemaBuilder(JKEY_TEMPLATE)
                 .setRequired(
{
    JKEY_TEMPLATE_ENGINE
});
auto templateEngine = templateS.addProperty(JKEY_TEMPLATE_ENGINE)
                      .addKeyValuePair("type", t_string);
auto templateOutputDirectory = templateS.addProperty(JKEY_TEMPLATE_OUTPUTDIRECTORY)
                               .addKeyValuePair("type", t_string);

// -------------------------------------------------------------------------- //
// FULL SCHEMA

auto templateB = JsonSchemaBuilder()
                 .addReference(JKEY_LOGGING, "logging")
                 .addReference(JKEY_TEMPLATE, "template")
                 .addSubSchema(logging)
                 .addSubSchema(templateS)
                 .setRequired(
{
    JKEY_TEMPLATE
});
const std::string SCHEMA_TEMPLATE_STRING = templateB.build();
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);
