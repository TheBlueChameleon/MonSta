#include "errorservice/errors.hpp"

#include "handleconverter.hpp"

using namespace nlohmann;

namespace JsonService
{
    // ---------------------------------------------------------------------- //
    // nlohmann handles

    IJsonServiceTypes::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonServiceTypes::JsonHandle
        {
            reinterpret_cast<decltype(IJsonServiceTypes::JsonHandle::data)>(&reference)
        };
    }

    IJsonServiceTypes::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonServiceTypes::ModifiableJsonHandle
        {
            reinterpret_cast<decltype(IJsonServiceTypes::ModifiableJsonHandle::data)>(&reference)
        };
    }

    const nlohmann::ordered_json& toOrderedJson(const IJsonServiceTypes::JsonHandle handle)
    {
        return *reinterpret_cast<const ordered_json*>(handle.data);
    }

    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonServiceTypes::ModifiableJsonHandle handle)
    {
        return *reinterpret_cast<ordered_json*>(
                   const_cast<void*>(handle.data)
               );
    }

    void assertSaneHandle(const IJsonServiceTypes::JsonHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Handle");
        }
    }

    void assertSaneTag(const IJsonServiceTypes::JsonTag tag)
    {
        if (tag.name == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Tag");
        }

        if (std::strlen(tag.name) == 0)
        {
            throw ClientRequestError("Client attempted operation on empty Json Tag");
        }
    }

    void assertSaneJsonPointer(const char* const jsonPointer)
    {
        if (jsonPointer == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Pointer");
        }

        if (std::strlen(jsonPointer) == 0)
        {
            throw ClientRequestError("Client attempted operation on empty Json Pointer");
        }
    }

    // ---------------------------------------------------------------------- //
    // JsonSchemaBuilder handles

    IJsonServiceTypes::JsonSchemaBuilderHandle toJsonSchemaBuilderHandle(JsonSchemaBuilder& reference)
    {
        return IJsonServiceTypes::JsonSchemaBuilderHandle
        {
            reinterpret_cast<decltype(IJsonServiceTypes::JsonSchemaBuilderHandle::data)>(&reference)
        };
    }

    IJsonServiceTypes::JsonSubSchemaBuilderHandle toJsonSubSchemaBuilderHandle(JsonSubSchemaBuilder& reference)
    {
        return IJsonServiceTypes::JsonSubSchemaBuilderHandle
        {
            reinterpret_cast<decltype(IJsonServiceTypes::JsonSubSchemaBuilderHandle::data)>(&reference)
        };
    }

    IJsonServiceTypes::JsonSchemaElementBuilderHandle toJsonSchemaElementBuilderHandle(JsonSchemaElementBuilder& reference)
    {
        return IJsonServiceTypes::JsonSchemaElementBuilderHandle
        {
            reinterpret_cast<decltype(IJsonServiceTypes::JsonSchemaElementBuilderHandle::data)>(&reference)
        };
    }

    JsonSchemaBuilder& toSchemaBuilder(IJsonServiceTypes::JsonSchemaBuilderHandle handle)
    {
        return *reinterpret_cast<JsonSchemaBuilder*>(handle.data);
    }

    JsonSubSchemaBuilder& toSubSchemaBuilder(IJsonServiceTypes::JsonSubSchemaBuilderHandle handle)
    {
        return *reinterpret_cast<JsonSubSchemaBuilder*>(handle.data);
    }

    JsonSchemaElementBuilder& toSchemaElementBuilder(IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        return *reinterpret_cast<JsonSchemaElementBuilder*>(handle.data);
    }

    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaBuilderHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null JsonSchemaBuilder Handle");
        }
    }

    void assertSaneHandle(const IJsonServiceTypes::JsonSubSchemaBuilderHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null JsonSubSchemaBuilder Handle");
        }
    }

    void assertSaneHandle(const IJsonServiceTypes::JsonSchemaElementBuilderHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null JsonSchemaElementBuilder Handle");
        }
    }

}
