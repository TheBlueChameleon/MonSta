#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
using namespace nlohmann;
#include <nlohmann/json-schema.hpp>
using namespace nlohmann::json_schema;

#include <IJsonService.hpp>

#include "errors.hpp"

#include "jsonservice.hpp"

namespace JsonService
{
    // ====================================================================== //
    // State

    static JsonServiceDatabase database;
    static bool allowComments = true;
    static bool allowExceptions = true;

    // ====================================================================== //
    // Internal

    static IJsonService::Handle toHandle(const nlohmann::json& reference)
    {
        return IJsonService::Handle(
                   reinterpret_cast<decltype(IJsonService::Handle::data)>(&reference)
               );
    }

    // ====================================================================== //
    // JsonDatabase

    IJsonService exportService()
    {
        return IJsonService();
    }

    JsonServiceDatabase& getDatabase()
    {
        return database;
    }

    std::optional<JsonServiceDatabase::EntryState> getState(const std::string_view tag)
    {
        return database.getState(tag);
    }

    const nlohmann::ordered_json& get(const std::string_view tag)
    {
        return database.get(tag);
    }

    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json& json)
    {
        return database.add(tag, json);
    }

    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json&& json)
    {
        return database.add(tag, std::move(json));
    }

    const nlohmann::ordered_json& getOrAdd(const std::string_view tag, std::function<nlohmann::ordered_json()> creator)
    {
        return database.getOrAdd(tag, creator);
    }

    std::optional<std::reference_wrapper<nlohmann::ordered_json> > declare(const std::string_view tag)
    {
        return database.declare(tag);
    }

    const nlohmann::ordered_json& commit(const std::string& tag)
    {
        return database.commit(tag);
    }

    // ====================================================================== //
    // Parsing & Validation

    void setAllowComments(bool value)
    {
        allowComments = value;
    }

    void setAllowExceptions(bool value)
    {
        allowExceptions = value;
    }

    nlohmann::ordered_json parse(const std::string_view data)
    {
        return ordered_json::parse(data, nullptr, allowExceptions, allowComments);
    }

    const ordered_json& parseAndAdd(const std::string_view tag, const std::string_view data)
    {
        return add(tag, parse(data));
    }

    json validate(
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema,
        const std::string_view origin
    )
    {
        json_validator validator;
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
            return validator.validate(data);
        }
        catch (const std::invalid_argument& e)
        {
            throw CriticalAbort(
                "JSON data from '"s + origin.data() + "' are invalid:\n" +
                e.what()
            );
        }
    }

    ordered_json validateAndPatch(const nlohmann::ordered_json& data, const nlohmann::ordered_json& schema, const std::string_view origin)
    {
        const auto patch = validate(data, schema, origin);
        return data.patch(patch);
    }

    const ordered_json& validatePatchAndAdd(const std::string_view tag, const nlohmann::ordered_json& data, const nlohmann::ordered_json& schema)
    {
        const auto validatedData = validateAndPatch(data, schema, tag);
        return add(tag, validatedData);
    }

    ordered_json read(const std::filesystem::path& file)
    {
        try
        {
            std::ifstream hFile(file);
            auto data = ordered_json::parse(hFile, nullptr, allowExceptions, allowComments);
            return data;
        }
        catch (const nlohmann::ordered_json::parse_error& err)
        {
            throw CriticalAbort(
                "Error parsing JSON file '"s + file.c_str() + "'\n" +
                err.what()
            );
        }
    }

    const ordered_json readAndAdd(const std::string_view tag, const std::filesystem::path& file)
    {
        return add(tag, read(file));
    }

    ordered_json readValidateAndPatch(const std::filesystem::path& file, const nlohmann::ordered_json& schema)
    {
        ordered_json rawJson = read(file);
        return validateAndPatch(rawJson, schema, file.c_str());
    }

    ordered_json readValidateByTagAndPatch(const std::filesystem::path& file, const std::string_view validationSchemaTag)
    {
        return readValidateAndPatch(file, get(validationSchemaTag));
    }

    const ordered_json& readValidateByTagPatchAndAdd(
        const std::string_view tag,
        const std::filesystem::path& file,
        const std::string_view validationSchemaTag
    )
    {
        const auto validatedJson = readValidateByTagAndPatch(file, validationSchemaTag);
        return add(tag, validatedJson);
    }

}
