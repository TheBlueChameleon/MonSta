#include "services.hpp"
#include "jsonservice.hpp"

namespace JsonService
{
    const IJsonService::Handle get(const char* const tag)
    {
        return jsonService().get(tag);
    }

    const IJsonService::Handle navigateTo(const IJsonService::Handle handle, const char* const jsonPointer)
    {
        return jsonService().navigateTo(handle, jsonPointer);
    }

    const bool contains(const IJsonService::Handle handle, const char* const elementName)
    {
        return jsonService().containts(handle, elementName);
    }

}
