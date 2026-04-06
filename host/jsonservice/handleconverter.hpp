#ifndef HANDLECONVERTER_HPP
#define HANDLECONVERTER_HPP

#include <nlohmann/json.hpp>

#include <services/IJsonService.hpp>

#include "jsonschemabuilder.hpp"

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // nlohmann handles

    IJsonServiceTypes::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference);
    IJsonServiceTypes::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference);

    const nlohmann::ordered_json& toOrderedJson(const IJsonServiceTypes::JsonHandle handle);
    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonServiceTypes::ModifiableJsonHandle handle);

    void assertSaneHandle(const IJsonServiceTypes::JsonHandle handle);
    void assertSaneTag(const IJsonServiceTypes::JsonTag tag);
    void assertSaneJsonPointer(const char* const jsonPointer);

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder handles

    IJsonServiceTypes::JsonSchemaBuilderHandle toJsonSchemaBuilderHandle(JsonSchemaBuilder& reference);
    IJsonServiceTypes::JsonSubSchemaBuilderHandle toJsonSubSchemaBuilderHandle(JsonSubSchemaBuilder& reference);
    IJsonServiceTypes::JsonSchemaElementBuilderHandle toJsonSchemaElementBuilderHandle(JsonSchemaElementBuilder &reference);

    JsonSchemaBuilder& toSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle handle);
    JsonSubSchemaBuilder& toSubSchemaBuilder(IJsonServiceTypes::JsonSubSchemaBuilderHandle handle);
    JsonSchemaElementBuilder& toSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);

    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaBuilderHandle handle);
    void assertSaneHandle(const IJsonServiceTypes::JsonSubSchemaBuilderHandle handle);
    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle);
}

#endif // HANDLECONVERTER_HPP
