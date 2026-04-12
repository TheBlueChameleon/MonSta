#include "services/services.hpp"

#include "jsonservice_itemaccess.hpp"

namespace JsonService
{
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
    const IJsonServiceTypes::JsonType getType(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getType(handle);
    }

    const bool isNull(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isNull(handle);
    }

    const bool isBoolean(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isBoolean(handle);
    }

    const bool isInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isInteger(handle);
    }

    const bool isUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isUnsigned(handle);
    }

    const bool isFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isFloat(handle);
    }

    const bool isString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isString(handle);
    }

    const bool isObject(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isObject(handle);
    }

    const bool isArray(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.isArray(handle);
    }

    const bool getAsBool(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsBool(handle);
    }

    const int getAsInteger(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsInteger(handle);
    }

    const unsigned long long getAsUnsigned(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsUnsigned(handle);
    }

    const double getAsFloat(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsFloat(handle);
    }

    const std::string_view getAsString(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getAsString(handle);
    }

    const int getArraySize(const IJsonServiceTypes::JsonHandle handle)
    {
        return jsonService().itemAccess.getArraySize(handle);
    }

    const IJsonServiceTypes::JsonHandle getArrayItem(const IJsonServiceTypes::JsonHandle handle, const int index)
    {
        return jsonService().itemAccess.getArrayItem(handle, index);
    }

    void setToNull(const IJsonServiceTypes::ModifiableJsonHandle handle)
    {
        return jsonService().itemAccess.setToNull(handle);
    }

    void setToBool(const IJsonServiceTypes::ModifiableJsonHandle handle, const bool value)
    {
        return jsonService().itemAccess.setToBool(handle, value);
    }

    void setToInteger(const IJsonServiceTypes::ModifiableJsonHandle handle, const int value)
    {
        return jsonService().itemAccess.setToInteger(handle, value);
    }

    void setToUnsigned(const IJsonServiceTypes::ModifiableJsonHandle handle, const unsigned int value)
    {
        return jsonService().itemAccess.setToUnsigned(handle, value);
    }

    void setToFloat(const IJsonServiceTypes::ModifiableJsonHandle handle, const double value)
    {
        return jsonService().itemAccess.setToFloat(handle, value);
    }

    void setToString(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view value)
    {
        return jsonService().itemAccess.setToString(handle, value.data());
    }

    void setToHandle(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToHandle(handle, source);
    }

    void setToArray(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToArray(handle, source);
    }

    void setToObject(const IJsonServiceTypes::ModifiableJsonHandle handle, const IJsonServiceTypes::JsonHandle source)
    {
        return jsonService().itemAccess.setToObject(handle, source);
    }

    void setToParseable(const IJsonServiceTypes::ModifiableJsonHandle handle, const std::string_view source)
    {
        return jsonService().itemAccess.setToParseable(handle, source.data());
    }

    MemoryService::MemoryBlock dump(const IJsonServiceTypes::JsonHandle handle, int indent)
    {
        return jsonService().itemAccess.dump(handle, indent);
    }
}
