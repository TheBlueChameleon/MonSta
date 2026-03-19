#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <Version.hpp>

extern const Version HOST_VERSION;
extern const Version MIN_CLIENT_VERSION;
extern const Version MAX_CLIENT_VERSION;

extern const std::string APP_NAME;
extern const std::string APP_VERSION;

extern const nlohmann::json SCHEMA_SIMULATION;
extern const nlohmann::json SCHEMA_TEMPLATE;

static constexpr auto JKEY_ENVIRONMENT = "environment";

#endif // CONSTANTS_HPP
