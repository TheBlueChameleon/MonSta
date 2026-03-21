#include <string>
using namespace std::string_literals;

#include "schemaconstants.hpp"
#include "schemaconstantsbuilder.hpp"
using namespace JsonSchemaBuilder;

using Json = nlohmann::json;

const std::string TEST = makeSubschemaRef("name", "desc");

const std::string SUBSCHEMA_LOGGER_STRING = makeSubSchemaDef(JKEY_LOGGING,
{
    // properties
    std::make_pair(JKEY_LOGGING_LOGFILE, dict_t({
        {
            "type", quoted("string")
        }
    })),
    std::make_pair(JKEY_LOGGING_LOGLEVEL, dict_t({
        {"type", quoted("integer")},
        {"minimum", "0"},
        {"maximum", "6"}
    }))
}
                                                       );

const std::string SUBSCHEMA_SIMULATOR_STRING = makeSubSchemaDef(JKEY_SIMULATOR,
{
    /* properties : */
    std::make_pair(JKEY_SIMULATOR_ENGINE, dict_t({
        {
            "type", quoted("string")
        }
    })),
    std::make_pair(JKEY_SIMULATOR_INPUTDIRECTORY, dict_t({
        {
            "type", quoted("string")
        }
    })),
    std::make_pair(JKEY_SIMULATOR_OUTPUTDIRECTORY, dict_t({
        {
            "type", quoted("string")
        }
    })),

    std::make_pair(JKEY_SIMULATOR_REPETITIONS, dict_t({
        {"type", quoted("integer")},
        {"minimum", "1"}
    })),
    std::make_pair(JKEY_SIMULATOR_MAXTURNS, dict_t({
        {"type", quoted("integer")},
        {"minimum", "1"}
    })),
    std::make_pair(JKEY_SIMULATOR_THREADCOUNT, dict_t({
        {"type", quoted("integer")},
        {"minimum", "1"}
    })),

    std::make_pair(JKEY_SIMULATOR_ARGS, dict_t({
        {
            "type", quoted("string")
        }
    }))
},
/* required = */ {JKEY_SIMULATOR_ENGINE}
                                                          );

const std::string SUBSCHEMA_MATCHDEFINITION_STRING = makeSubSchemaDef(JKEY_MATCHDEFINITION, {});

const std::string SCHEMA_SIMULATION_STRING = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",

    "properties": {
)"s
                                             + makeSubschemaRef(JKEY_LOGGING, "dsc") + ",\n"
                                             + makeSubschemaRef(JKEY_SIMULATOR, "dsc") + ",\n"
                                             + makeSubschemaRef(JKEY_MATCHDEFINITION , "dsc") + R"(    },
    "required": [)" + quoted(JKEY_SIMULATOR) + R"(],
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
