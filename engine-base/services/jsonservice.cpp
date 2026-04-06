#include "services.hpp"
#include "jsonservice.hpp"

namespace JsonService
{
    const IJsonServiceTypes::JsonHandle get(const IJsonServiceTypes::JsonTag tag)
    {
        return jsonService().database.get(tag);
    }

    const IJsonServiceTypes::JsonHandle navigateTo(
        const IJsonServiceTypes::JsonHandle handle,
        const std::string_view jsonPointer)
    {
        return jsonService().itemAccess.navigateTo(handle, jsonPointer.data());
    }

    const bool contains(const IJsonServiceTypes::JsonHandle handle, const std::string_view elementName)
    {
        return jsonService().itemAccess.containts(handle, elementName.data());
    }

    const bool isString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isString(handle);
    }

    const std::string_view getAsString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsString(handle);
    }

}
