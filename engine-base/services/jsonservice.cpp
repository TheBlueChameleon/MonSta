#include "services.hpp"
#include "jsonservice.hpp"

namespace JsonService
{
    const IJsonService::JsonHandle get(const IJsonService::JsonTag tag)
    {
        return jsonService().get(tag);
    }

    const IJsonService::JsonHandle navigateTo(
        const IJsonService::JsonHandle handle,
        const std::string_view jsonPointer)
    {
        return jsonService().navigateTo(handle, jsonPointer.data());
    }

    const bool contains(const IJsonService::JsonHandle handle, const std::string_view elementName)
    {
        return jsonService().containts(handle, elementName.data());
    }

    const bool isString(const IJsonService::JsonHandle handle)
    {
        return jsonService().isString(handle);
    }

    const std::string_view getAsString(const IJsonService::JsonHandle handle)
    {
        return jsonService().getAsString(handle);
    }

}
