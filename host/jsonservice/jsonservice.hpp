#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

#include <IJsonService.hpp>

#include "jsonschemabuilder.hpp"
#include "jsonservicedatabase.hpp"

namespace JsonService
{
    IJsonService exportService();

    // ---------------------------------------------------------------------- //
    // JsonDatabase

    enum class EntryState {NONEXISTENT, DECLARED, READY};

    JsonServiceDatabase& getDatabase();

    std::optional<JsonServiceDatabase::EntryState> getState(const std::string_view tag);
    const nlohmann::ordered_json& get(const std::string_view tag);
    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json& json);
    const nlohmann::ordered_json& add(const std::string_view tag, const nlohmann::ordered_json&& json);
    const nlohmann::ordered_json& getOrAdd(const std::string_view tag, std::function<nlohmann::ordered_json()> creator);
    std::optional<std::reference_wrapper<nlohmann::ordered_json>> declare(const std::string_view tag);
    const nlohmann::ordered_json& commit(const std::string& tag);

    const IJsonService::Handle get_dlx(const char* const tag);

    // ---------------------------------------------------------------------- //
    // Json compatibility layer

    const IJsonService::Handle navigateTo_dlx(const IJsonService::Handle handle, const char* const jsonPointer);
    const bool contains_dlx(const IJsonService::Handle handle, const char* const elementName);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

    void setAllowComments(bool value);
    void setAllowExceptions(bool value);

    nlohmann::ordered_json          parse(const std::string_view data);
    const nlohmann::ordered_json&   parseAndAdd(const std::string_view tag, const std::string_view data);

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
        const std::string_view tag,
        const nlohmann::ordered_json& data,
        const nlohmann::ordered_json& schema
    );

    nlohmann::ordered_json          read(const std::filesystem::path& file);
    const nlohmann::ordered_json    readAndAdd(const std::string_view tag, const std::filesystem::path& file);

    nlohmann::ordered_json readValidateAndPatch(
        const std::filesystem::path& file,
        const nlohmann::ordered_json& schema
    );
    nlohmann::ordered_json readValidateByTagAndPatch(
        const std::filesystem::path& file,
        const std::string_view validationSchemaTag
    );
    const nlohmann::ordered_json& readValidateByTagPatchAndAdd(
        const std::string_view tag,
        const std::filesystem::path& file,
        const std::string_view validationSchemaTag
    );

    // ---------------------------------------------------------------------- //
    // Schema Builder Operations

    /* patch(json, json) -> json
     * merge_patch(json, json)?  -> json
     *
     * json ops:
     * getHandle(tag) -> Handle
     * getHandleFromPath(tag, path) -> Handle
     * getElement(Handle, item) -> Handle
     * emplace(Handle, path, *) -> Handle
     * asString(Handle), ...
     *
     * json schema builder ops:
     * ???
     */
}

#endif // JSONSERVICE_HPP
