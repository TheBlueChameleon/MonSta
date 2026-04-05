#include "errorservice/errors.hpp"

#include "handleconverter.hpp"

using namespace nlohmann;

namespace JsonService
{
    IJsonService::JsonHandle toJsonHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonService::JsonHandle
        {
            reinterpret_cast<decltype(IJsonService::JsonHandle::data)>(&reference)
        };
    }

    IJsonService::ModifiableJsonHandle toModifiableJsonHandle(const nlohmann::ordered_json& reference)
    {
        return IJsonService::ModifiableJsonHandle
        {
            reinterpret_cast<decltype(IJsonService::ModifiableJsonHandle::data)>(&reference)
        };
    }

    const nlohmann::ordered_json& toOrderedJson(const IJsonService::JsonHandle handle)
    {
        return *reinterpret_cast<const ordered_json*>(handle.data);
    }

    nlohmann::ordered_json& toModifiableOrderedJson(const IJsonService::ModifiableJsonHandle handle)
    {
        return *reinterpret_cast<ordered_json*>(
                   const_cast<void*>(handle.data)
               );
    }

    void assertSaneHandle(const IJsonService::JsonHandle handle)
    {
        if (handle.data == nullptr)
        {
            throw ClientRequestError("Client attempted operation on null Json Handle");
        }
    }

    void assertSaneTag(const IJsonService::JsonTag tag)
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

}
