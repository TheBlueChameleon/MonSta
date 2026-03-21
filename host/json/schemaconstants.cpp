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

auto matchDefinition = JsonSubSchemaBuilder(JKEY_MATCHDEFINITION);

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
    JKEY_SIMULATOR
});
const std::string SCHEMA_SIMULATION_STRING = simulation.build();
const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

// ========================================================================== //
// SHARED

const std::string SCHEMA_TEMPLATE_STRING = R"(
{
})";
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);
