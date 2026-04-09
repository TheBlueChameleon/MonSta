#ifndef HANDLECONVERTER_HPP
#define HANDLECONVERTER_HPP

#include <nlohmann/json_fwd.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    class JsonSchemaBuilder;
    class JsonSubSchemaBuilder;
    class JsonSchemaElementBuilder;

    // ---------------------------------------------------------------------- //
    // nlohmann handles

    IJsonServiceTypes::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference);
    IJsonServiceTypes::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference);

    const nlohmann::ordered_json& toOrderedJson(const IJsonServiceTypes::JsonHandle handle);
    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonServiceTypes::ModifiableJsonHandle handle);

    void assertSaneHandle(const IJsonServiceTypes::JsonHandle handle);
    void assertSaneJsonPointer(const char* const jsonPointer);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder handles

    IJsonServiceTypes::JsonSchemaBuilderHandle toJsonSchemaBuilderHandle(JsonSchemaBuilder& reference);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle toJsonSchemaElementBuilderHandle(JsonSchemaElementBuilder& reference);

    JsonSchemaBuilder& toSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle handle);
    JsonSchemaElementBuilder& toSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);

    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaBuilderHandle handle);
    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);

    // ---------------------------------------------------------------------- //
    // misc

    void assertSaneTag(const IJsonServiceTypes::JsonTag tag);
    void assertSaneParseable(const char* const rawJson);
    void assertSaneFilename(const char* const file);
}

#endif // HANDLECONVERTER_HPP
