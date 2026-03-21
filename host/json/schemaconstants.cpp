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
auto& logfile = logging.addElement(JKEY_LOGGING_LOGFILE).add("type", t_string);
auto& loglevel = logging.addElement(JKEY_LOGGING_LOGLEVEL)
                 .add("type", t_integer)
                 .add("minimum", "0")
                 .add("maximum", "6");
const std::string SUBSCHEMA_LOGGER_STRING = logging.build();

// ========================================================================== //
// SIMULATION
// -------------------------------------------------------------------------- //
// simulator

auto simulator = JsonSubSchemaBuilder(JKEY_SIMULATOR)
                 .setRequired(
{
    JKEY_SIMULATOR_ENGINE
});
auto& engine = simulator.addElement(JKEY_SIMULATOR_ENGINE)
               .add("type", t_string);
auto& outputDirectory = simulator.addElement(JKEY_SIMULATOR_INPUTDIRECTORY)
                        .add("type", t_string);
auto& inputDirectory = simulator.addElement(JKEY_SIMULATOR_OUTPUTDIRECTORY)
                       .add("type", t_string);
auto& repetitions = simulator.addElement(JKEY_SIMULATOR_REPETITIONS)
                    .add("type", t_integer)
                    .add("minimum", "1");
auto& maxTurns = simulator.addElement(JKEY_SIMULATOR_MAXTURNS)
                 .add("type", t_integer)
                 .add("minimum", "1");
auto& threadCount = simulator.addElement(JKEY_SIMULATOR_THREADCOUNT)
                    .add("type", t_integer)
                    .add("minimum", "1");
auto& args = simulator.addElement(JKEY_SIMULATOR_ARGS)
             .add("type", t_string);
const std::string SUBSCHEMA_SIMULATOR_STRING = simulator.build();

// -------------------------------------------------------------------------- //
// match definition

auto matchDefinition = JsonSubSchemaBuilder(JKEY_MATCHDEFINITION);
const std::string SUBSCHEMA_MATCHDEFINITION_STRING = matchDefinition.build();

// ========================================================================== //
// FULL SCHEMA

const std::string SCHEMA_SIMULATION_STRING = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",

    "properties": {
)"s
                                             + JsonSchemaBuilderUtils::makeSubschemaRef(JKEY_LOGGING, "dsc") + ",\n"
                                             + JsonSchemaBuilderUtils::makeSubschemaRef(JKEY_SIMULATOR, "dsc") + ",\n"
                                             + JsonSchemaBuilderUtils::makeSubschemaRef(JKEY_MATCHDEFINITION , "dsc") + R"(    },
    "required": [)" + JsonSchemaBuilderUtils::quoted(JKEY_SIMULATOR) + R"(],
    "additionalProperties": false,

    "$defs" : {
)"s
                                             + SUBSCHEMA_LOGGER_STRING + ",\n"
                                             + SUBSCHEMA_SIMULATOR_STRING + ",\n"
                                             + SUBSCHEMA_MATCHDEFINITION_STRING + R"(
    }
})";
const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

const std::string SCHEMA_TEMPLATE_STRING = R"(
{
})";
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);
