#include "constants.hpp"
#include "api/versionservice.hpp"

const Version HOST_VERSION       = {0, 1, 0, 0};
const Version MIN_CLIENT_VERSION = {0, 1, 0, 0};

const std::string APP_NAME = "MonSta";
const std::string APP_VERSION = VersionService::to_string(HOST_VERSION);

const nlohmann::json SCHEMA_SIMULATION = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",

    "properties": {
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
        "environment" : {
            "properties": {
                "engine": {
                   "type": "string"
                },
                "logfile": {
                   "type": "string"
                },
                "reportfile": {
                   "type": "string"
                },
                "loglevel": {
                    "type": "integer",
                    "minimum": 0,
                    "maximum": 6
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
                "engine",
                "reportfile"
            ],
            "additionalProperties": false
        }
    }
}
)"_json;
const nlohmann::json SCHEMA_TEMPLATE;
