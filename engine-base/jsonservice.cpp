#include "services.hpp"
#include "jsonservice.hpp"

namespace JsonService
{
const IJsonService::JsonHandle get(const IJsonService::JsonTag tag)
    {
        return jsonService().get(tag);
    }

    const IJsonService::JsonHandle navigateTo(const IJsonService::JsonHandle handle, const char* const jsonPointer)
    {
        return jsonService().navigateTo(handle, jsonPointer);
    }

    const bool contains(const IJsonService::JsonHandle handle, const char* const elementName)
    {
        return jsonService().containts(handle, elementName);
    }

    const bool isString(const IJsonService::JsonHandle handle)
    {
        return jsonService().isString(handle);
    }

    const char* const getAsString(const IJsonService::JsonHandle handle)
    {
        return jsonService().getAsString(handle);
    }

}
