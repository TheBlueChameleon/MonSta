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

    const IJsonServiceTypes::EntryState getState(const IJsonServiceTypes::JsonTag tag);
    const nlohmann::ordered_json& get(const IJsonServiceTypes::JsonTag tag);
    const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& add(const IJsonServiceTypes::JsonTag tag, nlohmann::ordered_json&& json);
    const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, std::function<void(nlohmann::ordered_json&)> creator);
    const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& getOrAdd(const IJsonServiceTypes::JsonTag tag, nlohmann::ordered_json&& json);
    std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const IJsonServiceTypes::JsonTag tag);
    const nlohmann::ordered_json& commit(const IJsonServiceTypes::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    void setAllowComments(bool value);
    void setAllowExceptions(bool value);

    nlohmann::ordered_json          parse(const std::string_view data);
    const nlohmann::ordered_json&   parseAndAdd(const IJsonServiceTypes::JsonTag tag, const std::string_view data);

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
        const IJsonServiceTypes::JsonTag tag,
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema
    );

    nlohmann::ordered_json          read(const std::filesystem::path& file);
    const nlohmann::ordered_json    readAndAdd(const IJsonServiceTypes::JsonTag tag, const std::filesystem::path& file);

    nlohmann::ordered_json readValidateAndPatch(
        const std::filesystem::path& file,
        const nlohmann::ordered_json& schema
    );
    nlohmann::ordered_json readValidateByTagAndPatch(
        const std::filesystem::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    );
    const nlohmann::ordered_json& readValidateByTagPatchAndAdd(
        const IJsonServiceTypes::JsonTag tag,
        const std::filesystem::path& file,
        const IJsonServiceTypes::JsonTag validationSchemaTag
    );
}

#endif // JSONSERVICE_HPP
