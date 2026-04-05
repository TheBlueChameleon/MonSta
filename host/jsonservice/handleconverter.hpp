#ifndef HANDLECONVERTER_HPP
#define HANDLECONVERTER_HPP

#include <nlohmann/json.hpp>

#include <services/IJsonService.hpp>

namespace JsonService
{
    IJsonService::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference);

    IJsonService::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference);

    const nlohmann::ordered_json& toOrderedJson(const IJsonService::JsonHandle handle);

    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonService::ModifiableJsonHandle handle);

    void assertSaneHandle(const IJsonService::JsonHandle handle);

    void assertSaneTag(const IJsonService::JsonTag tag);

    void assertSaneJsonPointer(const char* const jsonPointer);
}

#endif // HANDLECONVERTER_HPP
