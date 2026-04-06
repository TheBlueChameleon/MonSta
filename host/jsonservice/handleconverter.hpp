#ifndef HANDLECONVERTER_HPP
#define HANDLECONVERTER_HPP

#include <nlohmann/json.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    IJsonServiceTypes::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference);

    IJsonServiceTypes::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference);

    const nlohmann::ordered_json& toOrderedJson(const IJsonServiceTypes::JsonHandle handle);

    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonServiceTypes::ModifiableJsonHandle handle);

    void assertSaneHandle(const IJsonServiceTypes::JsonHandle handle);

    void assertSaneTag(const IJsonServiceTypes::JsonTag tag);

    void assertSaneJsonPointer(const char* const jsonPointer);
}

#endif // HANDLECONVERTER_HPP
