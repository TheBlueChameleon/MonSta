#include <iostream>
#include <fstream>
#include <string>
using namespace std::string_literals;

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "../errors.hpp"

#include "jsonservice.hpp"

const nlohmann::json readJsonFile(const std::filesystem::path& source)
{
    using Json = nlohmann::json;

    try
    {
        std::ifstream hFile(source);
        Json data = Json::parse(hFile, nullptr, true, true);
        return data;
    }
    catch (const Json::parse_error& err)
    {
        throw CriticalAbort(
            "Error parsing JSON file '"s + source.c_str() + "'\n" +
            err.what()
        );
    }
}

void validateJsonAgainstJson(const nlohmann::json& data, const nlohmann::json& schema, const std::string& origin)
{
    using Json = nlohmann::json;
    using JsonValidator = nlohmann::json_schema::json_validator;

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
