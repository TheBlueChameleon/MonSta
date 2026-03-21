#include <string>
using namespace std::string_literals;

#include "constants.hpp"
#include "api/versionservice.hpp"

#define QUOTED(str) "\""s + str + "\""

#define PROPERTY_REFERENCE(propertyName, propertyDefinition) \
    "        "s + QUOTED(propertyName) + ": {\n" \
    "            " + QUOTED("$ref")        + ": " + QUOTED("#/$defs/" # propertyName) + ",\n" \
    "            " + QUOTED("description") + ": " + QUOTED(propertyDefinition) + "\n" \
    "        }"

using Json = nlohmann::json;

const std::string APP_NAME = "MonSta";
const std::string APP_VERSION = VersionService::to_string(HOST_VERSION);

const Version HOST_VERSION       = {0, 1, 0, 0};
const Version MIN_CLIENT_VERSION = {0, 1, 0, 0};
const Version MAX_CLIENT_VERSION = {2, 0, 0, 0};

const std::string SUBSCHEMA_DEFS_LOGGER_STRING =
    "        " + QUOTED(JKEY_LOGGING) + R"(: {
            "properties": {
                "logfile": {
                   "type": "string"
                },
                "loglevel": {
                    "type": "integer",
                    "minimum": 0,
                    "maximum": 6
                }
            },
            "additionalProperties": false
        })";

const std::string SUBSCHEMA_DEFS_SIMULATOR_STRING =
    "        " + QUOTED(JKEY_SIMULATOR) + R"(: {
            "properties": {
                "engine": {
                   "type": "string"
                },
                "inputDirectory": {
                   "type": "string"
                },
                "outputDirectory": {
                   "type": "string"
                },
                "repetitions": {
                    "type": "integer",
                    "minimum": 0
                },
                "maxTurns": {
                    "type": "integer",
                    "minimum": 0
                },
                "threadCount": {
                    "type": "integer",
                    "minimum": 0
                }
            },
            "required": ["engine"],
            "additionalProperties": false
})";

const std::string SCHEMA_SIMULATION_STRING = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",

    "properties": {
)"s
    + PROPERTY_REFERENCE(JKEY_LOGGING, "dsc") + ",\n"
    + PROPERTY_REFERENCE(JKEY_SIMULATOR, "dsc") + ",\n"
    + PROPERTY_REFERENCE(JKEY_MATCHDEFINITION , "dsc") + R"(    },
    "required": [)" + QUOTED(JKEY_SIMULATOR) + R"(],
    "additionalProperties": false,

    "$defs" : {
)"s
    + SUBSCHEMA_DEFS_LOGGER_STRING + ",\n"
    + SUBSCHEMA_DEFS_SIMULATOR_STRING + R"(
    }
}
)";
const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

const std::string SCHEMA_TEMPLATE_STRING = R"(
{}
)";
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);

