#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <nlohmann/json.hpp>

namespace JsonService
{
    const nlohmann::json readJsonFile(const char* const source);

    const nlohmann::json parseJson(const char* const json);

    void validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const char* const origin);
}

#endif // JSONSERVICE_HPP
