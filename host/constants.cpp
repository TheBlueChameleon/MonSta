#include "constants.hpp"
#include "api/versionutils.hpp"

const Version HOST_VERSION       = {0, 1, 0, 0};
const Version MIN_CLIENT_VERSION = {0, 1, 0, 0};

const std::string APP_NAME = "MonSta";
const std::string APP_VERSION = VersionUtils::to_string(HOST_VERSION);

const nlohmann::json SCHEMA_SIMULATION = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
        "environment": {
            "description": "Host side settings",
            "type": "object"
        },
        "matchDefinition": {
            "description": "foo",
            "type": "object"
        }
    },
    "required": ["environment"],
    "additionalProperties": false
}
)"_json;
const nlohmann::json SCHEMA_TEMPLATE;
