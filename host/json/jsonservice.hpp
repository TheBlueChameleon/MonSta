#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <nlohmann/json.hpp>

struct JsonService
{
    static const nlohmann::json readJsonFile(const char* const source);

    static const nlohmann::json parseJson(const char* const json);

    static void validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const char* const origin);
};

#endif // JSONSERVICE_HPP
