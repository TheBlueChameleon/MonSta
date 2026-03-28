#ifndef IJSONSERVICE_HPP
#define IJSONSERVICE_HPP

#include <nlohmann/json.hpp>

struct IJsonService
{
    struct Handle
    {
        void* data;
    };

    // ====================================================================== //
    // LEGACY

    const nlohmann::json(*readJsonFile)(const char* const source);

    const nlohmann::json(*parseJson)(const char* const json);

    void (*validateJsonAgainstJson)(const nlohmann::json& data,
                                    const nlohmann::json& schema,
                                    const char* const origin);
};

#endif // IJSONSERVICE_HPP
