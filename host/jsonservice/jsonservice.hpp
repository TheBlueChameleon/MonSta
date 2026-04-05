#ifndef JSONSERVICE_HPP
#define JSONSERVICE_HPP

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

    const IJsonService::EntryState getState_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle get_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle getOrAdd_dlx(
        const IJsonService::JsonTag tag,
        const void(*creator)(const IJsonService::ModifiableJsonHandle)
    );
    const IJsonService::JsonHandle getOrParse_dlx(
        const IJsonService::JsonTag tag,
        const char* const json
    );
    const IJsonService::ModifiableJsonHandle declare_dlx(const IJsonService::JsonTag tag);
    const IJsonService::JsonHandle commit_dlx(const IJsonService::JsonTag tag);

    // ---------------------------------------------------------------------- //
    // Json compatibility layer

    const IJsonService::JsonHandle navigateTo_dlx(const IJsonService::JsonHandle handle, const char* const jsonPointer);
    const bool contains_dlx(const IJsonService::JsonHandle handle, const char* const elementName);

    const IJsonService::JsonType getType_dlx(const IJsonService::JsonHandle handle);
    const bool isNull_dlx(const IJsonService::JsonHandle handle);
    const bool isBoolean_dlx(const IJsonService::JsonHandle handle);
    const bool isInteger_dlx(const IJsonService::JsonHandle handle);
    const bool isUnsigned_dlx(const IJsonService::JsonHandle handle);
    const bool isFloat_dlx(const IJsonService::JsonHandle handle);
    const bool isString_dlx(const IJsonService::JsonHandle handle);
    const bool isArray_dlx(const IJsonService::JsonHandle handle);
    const bool isObject_dlx(const IJsonService::JsonHandle handle);

    const bool getAsBool_dlx(const IJsonService::JsonHandle handle);
    const int getAsInteger_dlx(const IJsonService::JsonHandle handle);
    const unsigned long long getAsUnsigned_dlx(const IJsonService::JsonHandle handle);
    const double getAsFloat_dlx(const IJsonService::JsonHandle handle);
    const char* const getAsString_dlx(const IJsonService::JsonHandle handle);

    const int getArraySize_dlx(const IJsonService::JsonHandle handle);
    const IJsonService::JsonHandle getArrayItem_dlx(const IJsonService::JsonHandle handle, const int index);

    void setToNull_dlx(const IJsonService::ModifiableJsonHandle handle);
    void setToBool_dlx(const IJsonService::ModifiableJsonHandle handle, const bool value);
    void setToInteger_dlx(const IJsonService::ModifiableJsonHandle handle, const int value);
    void setToUnsigned_dlx(const IJsonService::ModifiableJsonHandle handle, const unsigned value);
    void setToFloat_dlx(const IJsonService::ModifiableJsonHandle handle, const double value);
    void setToString_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const value);
    void setToHandle_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToArray_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToObject_dlx(const IJsonService::ModifiableJsonHandle handle, const IJsonService::JsonHandle source);
    void setToParseable_dlx(const IJsonService::ModifiableJsonHandle handle, const char* const source);

    // ---------------------------------------------------------------------- //
    // Parsing & Validation

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

    const IJsonService::JsonHandle parseValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag     tag,
        const char* const               json,
        const IJsonService::JsonTag     validationSchemaTag
    );
    const IJsonService::JsonHandle readValidatePatchAndAdd_dlx(
        const IJsonService::JsonTag tag,
        const char* const file,
        const IJsonService::JsonTag validationSchemaTag
    );

    // ---------------------------------------------------------------------- //
    // Schema Builder Operations

    const IJsonService::JsonSchemaBuilderHandle    instantiateSchemaBuilder_dlx();
    const IJsonService::JsonSubSchemaBuilderHandle instantiateSubSchemaBuilder_dlx();
    const IJsonService::JsonElementBuilderHandle   instantiateElementBuilder_dlx();

    void freeSchemaBuilder_dlx(const IJsonService::JsonSchemaBuilderHandle*);
    void freeSubSchemaBuilder_dlx(const IJsonService::JsonSubSchemaBuilderHandle*);
    void freeElementBuilder_dlx(const IJsonService::JsonElementBuilderHandle*);
    /*
     * json schema builder ops:
     * ???
     */

    // ---------------------------------------------------------------------- //
    // Other

    /*
     * patch(json, json) -> json
     * merge_patch(json, json)?  -> json
     */
}

#endif // JSONSERVICE_HPP
