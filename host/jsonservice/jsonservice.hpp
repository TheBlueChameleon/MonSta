#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include <services/IJsonService.hpp>

#include "jsonschemabuilder.hpp"
#include "jsonservicedatabase.hpp"

namespace JsonService
{
    IJsonService exportService();

    // ---------------------------------------------------------------------- //
    // JsonDatabase

    JsonServiceDatabase& getDatabase();

    const IJsonService::EntryState getState(const IJsonService::JsonTag tag);
    const nlohmann::ordered_json& get(const IJsonService::JsonTag tag);
    const nlohmann::ordered_json& add(const IJsonService::JsonTag tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& add(const IJsonService::JsonTag tag, nlohmann::ordered_json&& json);
    const nlohmann::ordered_json& getOrAdd(const IJsonService::JsonTag tag, std::function<void(nlohmann::ordered_json&)> creator);
    const nlohmann::ordered_json& getOrAdd(const IJsonService::JsonTag tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& getOrAdd(const IJsonService::JsonTag tag, nlohmann::ordered_json&& json);
    std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const IJsonService::JsonTag tag);
    const nlohmann::ordered_json& commit(const IJsonService::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    // TODO: ...AndAdd functions should use getOrAdd

    void setAllowComments(bool value);
    void setAllowExceptions(bool value);

    nlohmann::ordered_json          parse(const std::string_view data);
    const nlohmann::ordered_json&   parseAndAdd(const IJsonService::JsonTag tag, const std::string_view data);

    nlohmann::json validate(
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema,
        const std::string_view origin
    );
    nlohmann::ordered_json validateAndPatch(
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema,
        const std::string_view origin
    );
    const nlohmann::ordered_json& validatePatchAndAdd(
        const IJsonService::JsonTag tag,
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema
    );

    nlohmann::ordered_json          read(const std::filesystem::path& file);
    const nlohmann::ordered_json    readAndAdd(const IJsonService::JsonTag tag, const std::filesystem::path& file);

    nlohmann::ordered_json readValidateAndPatch(
        const std::filesystem::path& file,
        const nlohmann::ordered_json& schema
    );
    nlohmann::ordered_json readValidateByTagAndPatch(
        const std::filesystem::path& file,
        const IJsonService::JsonTag validationSchemaTag
    );
    const nlohmann::ordered_json& readValidateByTagPatchAndAdd(
        const IJsonService::JsonTag tag,
        const std::filesystem::path& file,
        const IJsonService::JsonTag validationSchemaTag
    );
}

#endif // JSONSERVICE_HPP
