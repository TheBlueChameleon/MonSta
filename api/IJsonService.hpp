#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

#include <nlohmann/json.hpp>

struct IJsonService
{
    const nlohmann::json(*readJsonFile)(const std::filesystem::path& source);

    void (*validateJsonAgainstJson)(const nlohmann::json& data,
                                    const nlohmann::json& schema,
                                    const std::string& origin);
};

#endif // IJSONSERVICE_HPP
