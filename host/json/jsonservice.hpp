#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <nlohmann/json.hpp>

const nlohmann::json readJsonFile(const std::filesystem::path& source);
void validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const std::string& origin);

#endif // JSONSERVICE_HPP
