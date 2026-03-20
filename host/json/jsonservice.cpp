#include <iostream>
#include <fstream>
#include <string>
using namespace std::string_literals;

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "../errors.hpp"

#include "jsonservice.hpp"

using Json = nlohmann::json;
using JsonValidator = nlohmann::json_schema::json_validator;

const nlohmann::json JsonService::readJsonFile(const char* const source)
{
    try
    {
        std::ifstream hFile(source);
        Json data = Json::parse(hFile, nullptr, true, true);
        return data;
    }
    catch (const Json::parse_error& err)
    {
        throw CriticalAbort(
            "Error parsing JSON file '"s + source + "'\n" +
            err.what()
        );
    }
}

const nlohmann::json JsonService::parseJson(const char* const json)
{
    try
    {
        Json data = Json::parse(json, nullptr, true, true);
        return data;
    }
    catch (const Json::parse_error& err)
    {
        throw CriticalAbort(
            "Error parsing JSON data:\n"s + json + "\n" +
            err.what()
        );
    }
}

void JsonService::validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const char* const origin)
{
    JsonValidator validator;
    try
    {
        validator.set_root_schema(schema);
    }
    catch (const std::invalid_argument& e)
    {
        throw CriticalAbort(
            "Invalid state of simulation schema:\n"s +
            e.what()
        );
    }

    try
    {
        validator.validate(data);
    }
    catch (const std::invalid_argument& e)
    {
        throw CriticalAbort(
            "JSON data from '"s + origin + "' are invalid:\n" +
            e.what()
        );
    }
}
