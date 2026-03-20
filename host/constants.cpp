#include "constants.hpp"
#include "api/versionservice.hpp"

using Json = nlohmann::json;

const Version HOST_VERSION       = {0, 1, 0, 0};
const Version MIN_CLIENT_VERSION = {0, 1, 0, 0};
const Version MAX_CLIENT_VERSION = {2, 0, 0, 0};

const std::string APP_NAME = "MonSta";
const std::string APP_VERSION = VersionService::to_string(HOST_VERSION);

const std::string SCHEMA_SIMULATION_STRING = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",

    "properties": {
        "logging": {
            "description": "foo",
            "$ref": "#/$defs/logging"
        },
        "environment": {
            "description": "Host side settings",
            "$ref": "#/$defs/environment"
        },
        "matchDefinition": {
            "description": "foo",
            "type": "object"
        }
    },
    "required": ["environment"],
    "additionalProperties": false,

    "$defs" : {
        "logging": {
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
        },
        "environment" : {
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
            "required": [
                "engine"
            ],
            "additionalProperties": false
        }
    }
}
)";

const nlohmann::json SCHEMA_SIMULATION = Json::parse(SCHEMA_SIMULATION_STRING);

const std::string SCHEMA_TEMPLATE_STRING = R"(
{}
)";
const nlohmann::json SCHEMA_TEMPLATE = Json::parse(SCHEMA_TEMPLATE_STRING);
