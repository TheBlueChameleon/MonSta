#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <Version.hpp>

extern const std::string APP_NAME;
extern const std::string APP_VERSION;

extern const Version HOST_VERSION;
extern const Version MIN_CLIENT_VERSION;
extern const Version MAX_CLIENT_VERSION;

static constexpr auto JKEY_LOGGING          = "logging";
static constexpr auto JKEY_LOGGING_LOGFILE  = "logfile";
static constexpr auto JKEY_LOGGING_LOGLEVEL = "loglevel";

extern const std::string SUBSCHEMA_LOGGER_STRING;

static constexpr auto JKEY_SIMULATOR = "simulator";

extern const std::string SUBSCHEMA_SIMULATOR_STRING;

static constexpr auto JKEY_MATCHDEFINITION = "matchDefinition";

extern const std::string SUBSCHEMA_MATCHDEFINITION_STRING;

extern const std::string SCHEMA_SIMULATION_STRING;
extern const nlohmann::json SCHEMA_SIMULATION;

extern const std::string SCHEMA_TEMPLATE_STRING;
extern const nlohmann::json SCHEMA_TEMPLATE;

#endif // CONSTANTS_HPP
